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
typedef  int /*<<< orphan*/  zfs_handle_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  PROTO_NFS ; 
 scalar_t__ SHARED_NOT_SHARED ; 
 scalar_t__ zfs_is_shared_proto (int /*<<< orphan*/ *,char**,int /*<<< orphan*/ ) ; 

boolean_t
zfs_is_shared_nfs(zfs_handle_t *zhp, char **where)
{
	return (zfs_is_shared_proto(zhp, where,
	    PROTO_NFS) != SHARED_NOT_SHARED);
}