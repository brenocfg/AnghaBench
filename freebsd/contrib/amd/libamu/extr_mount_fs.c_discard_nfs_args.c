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

/* Variables and functions */
 scalar_t__ NFS_VERSION4 ; 
 int /*<<< orphan*/  discard_nfs23_args (void*) ; 
 int /*<<< orphan*/  discard_nfs4_args (void*) ; 

void
discard_nfs_args(void *nap, u_long nfs_version)
{
#ifdef HAVE_FS_NFS4
  if (nfs_version == NFS_VERSION4)
    discard_nfs4_args(nap);
  else
#endif /* HAVE_FS_NFS4 */
    discard_nfs23_args(nap);
}