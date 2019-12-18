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
struct backing_dev_info {int dummy; } ;
struct address_space {int /*<<< orphan*/ * a_ops; struct backing_dev_info* backing_dev_info; int /*<<< orphan*/ * assoc_mapping; scalar_t__ flags; int /*<<< orphan*/ * host; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  def_btnode_aops ; 
 int /*<<< orphan*/  mapping_set_gfp_mask (struct address_space*,int /*<<< orphan*/ ) ; 

void nilfs_btnode_cache_init(struct address_space *btnc,
			     struct backing_dev_info *bdi)
{
	btnc->host = NULL;  /* can safely set to host inode ? */
	btnc->flags = 0;
	mapping_set_gfp_mask(btnc, GFP_NOFS);
	btnc->assoc_mapping = NULL;
	btnc->backing_dev_info = bdi;
	btnc->a_ops = &def_btnode_aops;
}