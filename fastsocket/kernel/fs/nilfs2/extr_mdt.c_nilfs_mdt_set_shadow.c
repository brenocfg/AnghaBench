#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct inode {TYPE_1__* i_mapping; } ;
struct TYPE_5__ {struct TYPE_5__* assoc_mapping; } ;
struct TYPE_6__ {TYPE_2__ i_btnode_cache; } ;
struct TYPE_4__ {struct TYPE_4__* assoc_mapping; } ;

/* Variables and functions */
 TYPE_3__* NILFS_I (struct inode*) ; 

void nilfs_mdt_set_shadow(struct inode *orig, struct inode *shadow)
{
	shadow->i_mapping->assoc_mapping = orig->i_mapping;
	NILFS_I(shadow)->i_btnode_cache.assoc_mapping =
		&NILFS_I(orig)->i_btnode_cache;
}