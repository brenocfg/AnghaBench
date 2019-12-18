#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * dcr_cred; } ;
struct TYPE_6__ {TYPE_1__ dts_cred; } ;
typedef  TYPE_2__ dtrace_state_t ;
typedef  int /*<<< orphan*/  cred_t ;
struct TYPE_7__ {scalar_t__ cr_uid; scalar_t__ cr_ruid; scalar_t__ cr_suid; scalar_t__ cr_gid; scalar_t__ cr_rgid; scalar_t__ cr_sgid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dtrace_CRED () ; 
 TYPE_3__* posix_cred_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dtrace_priv_proc_common_user(dtrace_state_t *state)
{
	cred_t *cr, *s_cr = state->dts_cred.dcr_cred;

	/*
	 * We should always have a non-NULL state cred here, since if cred
	 * is null (anonymous tracing), we fast-path bypass this routine.
	 */
	ASSERT(s_cr != NULL);

	if ((cr = dtrace_CRED()) != NULL &&
	    posix_cred_get(s_cr)->cr_uid == posix_cred_get(cr)->cr_uid &&
	    posix_cred_get(s_cr)->cr_uid == posix_cred_get(cr)->cr_ruid &&
	    posix_cred_get(s_cr)->cr_uid == posix_cred_get(cr)->cr_suid &&
	    posix_cred_get(s_cr)->cr_gid == posix_cred_get(cr)->cr_gid &&
	    posix_cred_get(s_cr)->cr_gid == posix_cred_get(cr)->cr_rgid &&
	    posix_cred_get(s_cr)->cr_gid == posix_cred_get(cr)->cr_sgid)
		return (1);

	return (0);
}