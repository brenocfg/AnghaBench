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
struct vxlan_rdst {int /*<<< orphan*/  list; void* remote_ifindex; void* remote_vni; int /*<<< orphan*/  remote_port; int /*<<< orphan*/  remote_ip; } ;
struct vxlan_fdb {int /*<<< orphan*/  remotes; } ;
typedef  void* __u32 ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct vxlan_rdst* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct vxlan_rdst* vxlan_fdb_find_rdst (struct vxlan_fdb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,void*) ; 

__attribute__((used)) static int vxlan_fdb_append(struct vxlan_fdb *f,
			    __be32 ip, __be16 port, __u32 vni, __u32 ifindex)
{
	struct vxlan_rdst *rd;

	rd = vxlan_fdb_find_rdst(f, ip, port, vni, ifindex);
	if (rd)
		return 0;

	rd = kmalloc(sizeof(*rd), GFP_ATOMIC);
	if (rd == NULL)
		return -ENOBUFS;
	rd->remote_ip = ip;
	rd->remote_port = port;
	rd->remote_vni = vni;
	rd->remote_ifindex = ifindex;

	list_add_tail_rcu(&rd->list, &f->remotes);

	return 1;
}