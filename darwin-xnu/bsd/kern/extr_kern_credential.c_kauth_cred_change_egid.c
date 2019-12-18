#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* posix_cred_t ;
typedef  int /*<<< orphan*/  kauth_cred_t ;
typedef  scalar_t__ gid_t ;
struct TYPE_3__ {int cr_ngroups; scalar_t__* cr_groups; int cr_flags; } ;

/* Variables and functions */
 int CRF_NOMEMBERD ; 
 int /*<<< orphan*/  DEBUG_CRED_CHANGE (char*) ; 
 scalar_t__ kauth_cred_getgid (int /*<<< orphan*/ ) ; 
 scalar_t__ kauth_cred_ismember_gid (int /*<<< orphan*/ ,scalar_t__,int*) ; 
 TYPE_1__* posix_cred_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
kauth_cred_change_egid(kauth_cred_t cred, gid_t new_egid)
{
	int	i;
	int	displaced = 1;
#if radar_4600026
	int	is_member;
#endif	/* radar_4600026 */
	gid_t	old_egid = kauth_cred_getgid(cred);
	posix_cred_t pcred = posix_cred_get(cred);

	/* Ignoring the first entry, scan for a match for the new egid */
	for (i = 1; i < pcred->cr_ngroups; i++) {
		/*
		 * If we find a match, swap them so we don't lose overall
		 * group information
		 */
		if (pcred->cr_groups[i] == new_egid) {
			pcred->cr_groups[i] = old_egid;
			DEBUG_CRED_CHANGE("kauth_cred_change_egid: unset displaced\n");
			displaced = 0;
			break;
		}
	}

#if radar_4600026
#error Fix radar 4600026 first!!!

/*
This is correct for memberd behaviour, but incorrect for POSIX; to address
this, we would need to automatically opt-out any SUID/SGID binary, and force
it to use initgroups to opt back in.  We take the approach of considering it
opt'ed out in any group of 16 displacement instead, since it's a much more
conservative approach (i.e. less likely to cause things to break).
*/

	/*
	 * If we displaced a member of the supplementary groups list of the
	 * credential, and we have not opted out of memberd, then if memberd
	 * says that the credential is a member of the group, then it has not
	 * actually been displaced.
	 *
	 * NB:	This is typically a cold code path.
	 */
	if (displaced && !(pcred->cr_flags & CRF_NOMEMBERD) &&
	    kauth_cred_ismember_gid(cred, new_egid, &is_member) == 0 &&
	    is_member) {
	    	displaced = 0;
		DEBUG_CRED_CHANGE("kauth_cred_change_egid: reset displaced\n");
	}
#endif	/* radar_4600026 */

	/* set the new EGID into the old spot */
	pcred->cr_groups[0] = new_egid;

	return (displaced);
}