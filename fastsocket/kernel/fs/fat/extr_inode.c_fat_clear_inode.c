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
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fat_cache_inval_inode (struct inode*) ; 
 int /*<<< orphan*/  fat_detach (struct inode*) ; 

__attribute__((used)) static void fat_clear_inode(struct inode *inode)
{
	fat_cache_inval_inode(inode);
	fat_detach(inode);
}