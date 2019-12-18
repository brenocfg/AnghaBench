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
struct nfs_parsed_mount_data {unsigned int auth_flavor_len; scalar_t__* auth_flavors; } ;
struct nfs_mount_request {unsigned int* auth_flav_len; scalar_t__* auth_flavs; } ;

/* Variables and functions */
 int EACCES ; 
 int /*<<< orphan*/  MOUNT ; 
 int /*<<< orphan*/  dfprintk (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  nfs_umount (struct nfs_mount_request*) ; 

__attribute__((used)) static int nfs_walk_authlist(struct nfs_parsed_mount_data *args,
			     struct nfs_mount_request *request)
{
	unsigned int i, j, server_authlist_len = *(request->auth_flav_len);

	/*
	 * Certain releases of Linux's mountd return an empty
	 * flavor list.  To prevent behavioral regression with
	 * these servers (ie. rejecting mounts that used to
	 * succeed), revert to pre-2.6.32 behavior (no checking)
	 * if the returned flavor list is empty.
	 */
	if (server_authlist_len == 0)
		return 0;

	/*
	 * We avoid sophisticated negotiating here, as there are
	 * plenty of cases where we can get it wrong, providing
	 * either too little or too much security.
	 *
	 * RFC 2623, section 2.7 suggests we SHOULD prefer the
	 * flavor listed first.  However, some servers list
	 * AUTH_NULL first.  Our caller plants AUTH_SYS, the
	 * preferred default, in args->auth_flavors[0] if user
	 * didn't specify sec= mount option.
	 */
	for (i = 0; i < args->auth_flavor_len; i++)
		for (j = 0; j < server_authlist_len; j++)
			if (args->auth_flavors[i] == request->auth_flavs[j]) {
				dfprintk(MOUNT, "NFS: using auth flavor %d\n",
					request->auth_flavs[j]);
				args->auth_flavors[0] = request->auth_flavs[j];
				return 0;
			}

	dfprintk(MOUNT, "NFS: server does not support requested auth flavor\n");
	nfs_umount(request);
	return -EACCES;
}