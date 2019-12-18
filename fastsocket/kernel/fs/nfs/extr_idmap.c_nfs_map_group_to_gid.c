#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nfs_server {TYPE_1__* nfs_client; } ;
struct idmap {int /*<<< orphan*/  idmap_group_hash; } ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_2__ {struct idmap* cl_idmap; } ;

/* Variables and functions */
 int EINVAL ; 
 int nfs_idmap_id (struct idmap*,int /*<<< orphan*/ *,char const*,size_t,int /*<<< orphan*/ *) ; 
 int nfs_idmap_lookup_id (char const*,size_t,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ nfs_map_string_to_numeric (char const*,size_t,int /*<<< orphan*/ *) ; 

int nfs_map_group_to_gid(const struct nfs_server *server, const char *name, size_t namelen, __u32 *gid)
{
	struct idmap *idmap = server->nfs_client->cl_idmap;
	int ret = -EINVAL;

	if (nfs_map_string_to_numeric(name, namelen, gid))
		return 0;
	ret = nfs_idmap_lookup_id(name, namelen, "gid", gid);
	if (ret < 0)
		ret = nfs_idmap_id(idmap, &idmap->idmap_group_hash, name, namelen, gid);
	return ret;
}