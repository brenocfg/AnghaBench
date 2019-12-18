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
struct stripe_head {TYPE_2__* dev; TYPE_1__* raid_conf; } ;
struct page {int dummy; } ;
struct TYPE_4__ {struct page* page; } ;
struct TYPE_3__ {int pool_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int grow_buffers(struct stripe_head *sh)
{
	int i;
	int num = sh->raid_conf->pool_size;

	for (i = 0; i < num; i++) {
		struct page *page;

		if (!(page = alloc_page(GFP_KERNEL))) {
			return 1;
		}
		sh->dev[i].page = page;
	}
	return 0;
}