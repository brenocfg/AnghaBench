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
typedef  int /*<<< orphan*/  uid_t ;
struct persona {int /*<<< orphan*/  pna_login; int /*<<< orphan*/  pna_type; int /*<<< orphan*/  pna_id; } ;
struct kpersona_info {unsigned int persona_ngroups; int /*<<< orphan*/  persona_name; int /*<<< orphan*/  persona_gmuid; int /*<<< orphan*/  persona_groups; int /*<<< orphan*/  persona_gid; int /*<<< orphan*/  persona_type; int /*<<< orphan*/  persona_id; int /*<<< orphan*/  persona_info_version; } ;
typedef  int /*<<< orphan*/  persona_id ;
typedef  int /*<<< orphan*/  kinfo ;

/* Variables and functions */
 int ESRCH ; 
 int /*<<< orphan*/  MAXLOGNAME ; 
 int /*<<< orphan*/  NGROUPS ; 
 int /*<<< orphan*/  PERSONA_INFO_V1 ; 
 int copyin (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int kpersona_copyout (struct kpersona_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct kpersona_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  persona_dbg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  persona_get_gid (struct persona*) ; 
 int /*<<< orphan*/  persona_get_gmuid (struct persona*) ; 
 int /*<<< orphan*/  persona_get_groups (struct persona*,unsigned int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct persona* persona_lookup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  persona_put (struct persona*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kpersona_info_syscall(user_addr_t idp, user_addr_t infop)
{
	int error;
	uid_t persona_id;
	struct persona *persona;
	struct kpersona_info kinfo;

	error = copyin(idp, &persona_id, sizeof(persona_id));
	if (error)
		return error;

	/*
	 * TODO: rdar://problem/19981151
	 * Add entitlement check!
	 */

	persona = persona_lookup(persona_id);
	if (!persona)
		return ESRCH;

	persona_dbg("FOUND: persona: id:%d, gid:%d, login:\"%s\"",
		    persona->pna_id, persona_get_gid(persona),
		    persona->pna_login);

	memset(&kinfo, 0, sizeof(kinfo));
	kinfo.persona_info_version = PERSONA_INFO_V1;
	kinfo.persona_id = persona->pna_id;
	kinfo.persona_type = persona->pna_type;
	kinfo.persona_gid = persona_get_gid(persona);
	unsigned ngroups = 0;
	persona_get_groups(persona, &ngroups, kinfo.persona_groups, NGROUPS);
	kinfo.persona_ngroups = ngroups;
	kinfo.persona_gmuid = persona_get_gmuid(persona);

	/*
	 * NULL termination is assured b/c persona_name is
	 * exactly MAXLOGNAME + 1 bytes (and has been memset to 0)
	 */
	strncpy(kinfo.persona_name, persona->pna_login, MAXLOGNAME);

	persona_put(persona);

	error = kpersona_copyout(&kinfo, infop);

	return error;
}