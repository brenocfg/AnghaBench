#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct TYPE_6__ {int flag; } ;
typedef  TYPE_1__ dxd_t ;
struct TYPE_7__ {TYPE_1__ ea; } ;

/* Variables and functions */
 int DXD_EXTENT ; 
 TYPE_5__* JFS_IP (struct inode*) ; 
 int /*<<< orphan*/  addressDXD (TYPE_1__*) ; 
 int /*<<< orphan*/  dbFree (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invalidate_dxd_metapages (struct inode*,TYPE_1__) ; 
 int /*<<< orphan*/  lengthDXD (TYPE_1__*) ; 

__attribute__((used)) static inline void free_ea_wmap(struct inode *inode)
{
	dxd_t *ea = &JFS_IP(inode)->ea;

	if (ea->flag & DXD_EXTENT) {
		/* free EA pages from cache */
		invalidate_dxd_metapages(inode, *ea);
		dbFree(inode, addressDXD(ea), lengthDXD(ea));
	}
	ea->flag = 0;
}