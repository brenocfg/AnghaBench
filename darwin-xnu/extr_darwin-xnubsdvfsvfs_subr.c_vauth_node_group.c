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
struct vnode_attr {int /*<<< orphan*/  va_gid; } ;
typedef  int /*<<< orphan*/  kauth_cred_t ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ VATTR_IS_SUPPORTED (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int kauth_cred_ismember_gid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  va_gid ; 

__attribute__((used)) static int
vauth_node_group(struct vnode_attr *vap, kauth_cred_t cred, int *ismember, int idontknow)
{
	int	error;
	int	result;

	error = 0;
	result = 0;

	/*
	 * The caller is expected to have asked the filesystem for a group
	 * at some point prior to calling this function.  The answer may
	 * have been that there is no group ownership supported for the
	 * vnode object, in which case we return
	 */
	if (vap && VATTR_IS_SUPPORTED(vap, va_gid)) {
		error = kauth_cred_ismember_gid(cred, vap->va_gid, &result);
		/*
		 * Credentials which are opted into external group membership
		 * resolution which are not known to the external resolver
		 * will result in an ENOENT error.  We translate this into
		 * the appropriate 'idontknow' response for our caller.
		 *
		 * XXX We do not make a distinction here between an ENOENT
		 * XXX arising from a response from the external resolver,
		 * XXX and an ENOENT which is internally generated.  This is
		 * XXX a deficiency of the published kauth_cred_ismember_gid()
		 * XXX KPI which can not be overcome without new KPI.  For
		 * XXX all currently known cases, however, this wil result
		 * XXX in correct behaviour.
		 */
		if (error == ENOENT)
			error = idontknow;
	}
	/*
	 * XXX We could test the group UUID here if we had a policy for it,
	 * XXX but this is problematic from the perspective of synchronizing
	 * XXX group UUID and POSIX GID ownership of a file and keeping the
	 * XXX values coherent over time.  The problem is that the local
	 * XXX system will vend transient group UUIDs for unknown POSIX GID
	 * XXX values, and these are not persistent, whereas storage of values
	 * XXX is persistent.  One potential solution to this is a local
	 * XXX (persistent) replica of remote directory entries and vended
	 * XXX local ids in a local directory server (think in terms of a
	 * XXX caching DNS server).
	 */

	if (!error)
		*ismember = result;
	return(error);
}