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
typedef  int mode_t ;
typedef  int /*<<< orphan*/  kauth_cred_t ;
typedef  scalar_t__ id_t ;

/* Variables and functions */
 int EACCES ; 
 int S_IRWXG ; 
 int S_IRWXO ; 
 int S_IRWXU ; 
 scalar_t__ kauth_cred_getuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_cred_ismember_gid (int /*<<< orphan*/ ,scalar_t__,int*) ; 

int
posix_cred_access(kauth_cred_t cred, id_t object_uid, id_t object_gid, mode_t object_mode, mode_t mode_req)
{
	int is_member;
	mode_t mode_owner = (object_mode & S_IRWXU);
	mode_t mode_group = (object_mode & S_IRWXG) << 3;
	mode_t mode_world = (object_mode & S_IRWXO) << 6;

	/*
	 * Check first for owner rights
	 */
	if (kauth_cred_getuid(cred) == object_uid && (mode_req & mode_owner) == mode_req)
		return (0);

	/*
	 * Combined group and world rights check, if we don't have owner rights
	 *
	 * OPTIMIZED: If group and world rights would grant the same bits, and
	 * they set of requested bits is in both, then we can simply check the
	 * world rights, avoiding a group membership check, which is expensive.
	 */
	if ((mode_req & mode_group & mode_world) == mode_req) {
		return (0);
	} else {
		/*
		 * NON-OPTIMIZED: requires group membership check.
		 */
		if ((mode_req & mode_group) != mode_req) {
			/*
			 * exclusion group : treat errors as "is a member"
			 *
			 * NON-OPTIMIZED: +group would deny; must check group
			 */
			if (!kauth_cred_ismember_gid(cred, object_gid, &is_member) && is_member) {
				/*
				 * DENY: +group denies
				 */
				return (EACCES);
			} else {
				if ((mode_req & mode_world) != mode_req) {
					/*
					 * DENY: both -group & world would deny
					 */
					return (EACCES);
				} else {
					/*
					 * ALLOW: allowed by -group and +world
					 */
					return (0);
				}
			}
		} else {
			/*
			 * inclusion group; treat errors as "not a member"
			 *
			 * NON-OPTIMIZED: +group allows, world denies; must
			 * check group
			 */
			if (!kauth_cred_ismember_gid(cred, object_gid, &is_member) && is_member) {
				/*
				 * ALLOW: allowed by +group
				 */
				return (0);
			} else {
				if ((mode_req & mode_world) != mode_req) {
					/*
					 * DENY: both -group & world would deny
					 */
					return (EACCES);
				} else {
					/*
					 * ALLOW: allowed by -group and +world
					 */
					return (0);
				}
			}
		}
	}
}