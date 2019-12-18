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
struct pnfs_layoutdriver_type {int dummy; } ;
struct nfs_client {int dummy; } ;
struct nfs4_deviceid_node {int dummy; } ;
struct nfs4_deviceid {int dummy; } ;

/* Variables and functions */
 struct nfs4_deviceid_node* _find_get_deviceid (struct pnfs_layoutdriver_type const*,struct nfs_client const*,struct nfs4_deviceid const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_deviceid_hash (struct nfs4_deviceid const*) ; 

struct nfs4_deviceid_node *
nfs4_find_get_deviceid(const struct pnfs_layoutdriver_type *ld,
		       const struct nfs_client *clp, const struct nfs4_deviceid *id)
{
	return _find_get_deviceid(ld, clp, id, nfs4_deviceid_hash(id));
}