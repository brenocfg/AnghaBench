#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pnfs_layout_segment {int dummy; } ;
struct nfs4_deviceid_node {int dummy; } ;
struct TYPE_4__ {TYPE_1__* dsaddr; } ;
struct TYPE_3__ {struct nfs4_deviceid_node id_node; } ;

/* Variables and functions */
 TYPE_2__* FILELAYOUT_LSEG (struct pnfs_layout_segment*) ; 

__attribute__((used)) static inline struct nfs4_deviceid_node *
FILELAYOUT_DEVID_NODE(struct pnfs_layout_segment *lseg)
{
	return &FILELAYOUT_LSEG(lseg)->dsaddr->id_node;
}