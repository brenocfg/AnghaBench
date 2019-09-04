#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  scalar_t__ uid_t ;
struct persona {scalar_t__ pna_id; } ;
struct kpersona_info {char* persona_name; scalar_t__ persona_id; scalar_t__ persona_ngroups; scalar_t__ persona_gmuid; int /*<<< orphan*/  persona_groups; scalar_t__ persona_gid; int /*<<< orphan*/  persona_type; } ;

/* Variables and functions */
 int EPERM ; 
 scalar_t__ KAUTH_UID_NONE ; 
 scalar_t__ PERSONA_ID_NONE ; 
 int /*<<< orphan*/  assert (int) ; 
 int copyout (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kauth_cred_get () ; 
 int /*<<< orphan*/  kauth_cred_issuser (int /*<<< orphan*/ ) ; 
 int kpersona_copyin (int /*<<< orphan*/ ,struct kpersona_info*) ; 
 int kpersona_copyout (struct kpersona_info*,int /*<<< orphan*/ ) ; 
 struct persona* persona_alloc (scalar_t__,char const*,int /*<<< orphan*/ ,int*) ; 
 int persona_init_begin (struct persona*) ; 
 int /*<<< orphan*/  persona_init_end (struct persona*,int) ; 
 int /*<<< orphan*/  persona_put (struct persona*) ; 
 int persona_set_gid (struct persona*,scalar_t__) ; 
 int persona_set_groups (struct persona*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int kpersona_alloc_syscall(user_addr_t infop, user_addr_t idp)
{
	int error;
	struct kpersona_info kinfo;
	struct persona *persona;
	uid_t id = PERSONA_ID_NONE;
	const char *login;

	/*
	 * TODO: rdar://problem/19981151
	 * Add entitlement check!
	 */
	if (!kauth_cred_issuser(kauth_cred_get()))
		return EPERM;

	error = kpersona_copyin(infop, &kinfo);
	if (error)
		return error;

	login = kinfo.persona_name[0] ? kinfo.persona_name : NULL;
	if (kinfo.persona_id != PERSONA_ID_NONE && kinfo.persona_id != (uid_t)0)
		id = kinfo.persona_id;

	error = 0;
	persona = persona_alloc(id, login, kinfo.persona_type, &error);
	if (!persona)
		return error;

	error = persona_init_begin(persona);
	if (error) {
		goto out_persona_err;
	}

	if (kinfo.persona_gid) {
		error = persona_set_gid(persona, kinfo.persona_gid);
		if (error)
			goto out_persona_err;
	}

	if (kinfo.persona_ngroups > 0) {
		/* force gmuid 0 to *opt-out* of memberd */
		if (kinfo.persona_gmuid == 0)
			kinfo.persona_gmuid = KAUTH_UID_NONE;

		error = persona_set_groups(persona, kinfo.persona_groups,
					   kinfo.persona_ngroups,
					   kinfo.persona_gmuid);
		if (error)
			goto out_persona_err;
	}

	error = copyout(&persona->pna_id, idp, sizeof(persona->pna_id));
	if (error) {
		goto out_persona_err;
	}

	kinfo.persona_id = persona->pna_id;
	error = kpersona_copyout(&kinfo, infop);
	if (error) {
		goto out_persona_err;
	}

	persona_init_end(persona, error);

	/*
	 * On success, we have a persona structure in the global list with a
	 * single reference count on it. The corresponding _dealloc() call
	 * will release this reference.
	 */
	return error;

out_persona_err:
	assert(error != 0);
	persona_init_end(persona, error);

#if PERSONA_DEBUG
	printf("%s:  ERROR:%d\n", __func__, error);
#endif
	if (persona)
		persona_put(persona);
	return error;
}