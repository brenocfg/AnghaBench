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
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cache_change_attribute; } ;

/* Variables and functions */
 TYPE_1__* NFS_I (struct inode*) ; 

void nfs_force_lookup_revalidate(struct inode *dir)
{
	NFS_I(dir)->cache_change_attribute++;
}