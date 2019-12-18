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
struct address_space {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  invalidate_mapping_pages (struct address_space*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  truncate_inode_pages (struct address_space*,int /*<<< orphan*/ ) ; 

void nilfs_btnode_cache_clear(struct address_space *btnc)
{
	invalidate_mapping_pages(btnc, 0, -1);
	truncate_inode_pages(btnc, 0);
}