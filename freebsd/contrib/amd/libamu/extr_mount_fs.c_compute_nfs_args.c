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
typedef  scalar_t__ u_long ;
struct sockaddr_in {int dummy; } ;
struct netconfig {int dummy; } ;
typedef  int /*<<< orphan*/  mntent_t ;
typedef  int /*<<< orphan*/  am_nfs_handle_t ;

/* Variables and functions */
 scalar_t__ NFS_VERSION4 ; 
 int /*<<< orphan*/  compute_nfs23_args (void*,int /*<<< orphan*/ *,int,struct netconfig*,struct sockaddr_in*,scalar_t__,char*,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  compute_nfs4_args (void*,int /*<<< orphan*/ *,int,struct netconfig*,struct sockaddr_in*,scalar_t__,char*,int /*<<< orphan*/ *,char*,char*) ; 

void
compute_nfs_args(void *nap,
                 mntent_t *mntp,
                 int genflags,
                 struct netconfig *nfsncp,
                 struct sockaddr_in *ip_addr,
                 u_long nfs_version,
                 char *nfs_proto,
                 am_nfs_handle_t *fhp,
                 char *host_name,
                 char *fs_name)
{
#ifdef HAVE_FS_NFS4
  if (nfs_version == NFS_VERSION4)
    compute_nfs4_args(nap, mntp, genflags, nfsncp, ip_addr, nfs_version,
		      nfs_proto, fhp, host_name, fs_name);
  else
#endif /* HAVE_FS_NFS4 */
    compute_nfs23_args(nap, mntp, genflags, nfsncp, ip_addr, nfs_version,
		       nfs_proto, fhp, host_name, fs_name);
}