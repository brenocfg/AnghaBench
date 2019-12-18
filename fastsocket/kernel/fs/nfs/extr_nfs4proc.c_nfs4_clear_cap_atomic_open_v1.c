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
struct nfs_server {int caps; } ;
struct nfs4_exception {int retry; } ;

/* Variables and functions */
 int EINVAL ; 
 int NFS_CAP_ATOMIC_OPEN_V1 ; 

__attribute__((used)) static bool nfs4_clear_cap_atomic_open_v1(struct nfs_server *server,
		int err, struct nfs4_exception *exception)
{
	if (err != -EINVAL)
		return false;
	if (!(server->caps & NFS_CAP_ATOMIC_OPEN_V1))
		return false;
	server->caps &= ~NFS_CAP_ATOMIC_OPEN_V1;
	exception->retry = 1;
	return true;
}