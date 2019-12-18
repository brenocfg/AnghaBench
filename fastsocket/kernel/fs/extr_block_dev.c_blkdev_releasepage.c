#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct super_block {TYPE_3__* s_op; } ;
struct page {TYPE_2__* mapping; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_5__ {struct super_block* bd_super; } ;
struct TYPE_8__ {TYPE_1__ bdev; } ;
struct TYPE_7__ {int (* bdev_try_to_free_page ) (struct super_block*,struct page*,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 TYPE_4__* BDEV_I (int /*<<< orphan*/ ) ; 
 int stub1 (struct super_block*,struct page*,int /*<<< orphan*/ ) ; 
 int try_to_free_buffers (struct page*) ; 

__attribute__((used)) static int blkdev_releasepage(struct page *page, gfp_t wait)
{
	struct super_block *super = BDEV_I(page->mapping->host)->bdev.bd_super;

	if (super && super->s_op->bdev_try_to_free_page)
		return super->s_op->bdev_try_to_free_page(super, page, wait);

	return try_to_free_buffers(page);
}