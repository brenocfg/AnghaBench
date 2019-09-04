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
struct persona {int dummy; } ;
typedef  int /*<<< orphan*/  persona_id ;

/* Variables and functions */
 int EPERM ; 
 int ESRCH ; 
 int copyin (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kauth_cred_get () ; 
 int /*<<< orphan*/  kauth_cred_issuser (int /*<<< orphan*/ ) ; 
 struct persona* persona_lookup_and_invalidate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  persona_put (struct persona*) ; 

__attribute__((used)) static int kpersona_dealloc_syscall(user_addr_t idp)
{
	int error = 0;
	uid_t persona_id;
	struct persona *persona;

	if (!kauth_cred_issuser(kauth_cred_get()))
		return EPERM;

	error = copyin(idp, &persona_id, sizeof(persona_id));
	if (error)
		return error;

	/* invalidate the persona (deny subsequent spawn/fork) */
	persona = persona_lookup_and_invalidate(persona_id);

	if (!persona)
		return ESRCH;

	/* one reference from the _lookup() */
	persona_put(persona);

	/* one reference from the _alloc() */
	persona_put(persona);

	return error;
}