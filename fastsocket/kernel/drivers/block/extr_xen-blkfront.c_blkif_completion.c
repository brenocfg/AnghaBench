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
struct TYPE_4__ {int nr_segments; TYPE_1__* seg; } ;
struct blk_shadow {TYPE_2__ req; } ;
struct TYPE_3__ {int /*<<< orphan*/  gref; } ;

/* Variables and functions */
 int /*<<< orphan*/  gnttab_end_foreign_access (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void blkif_completion(struct blk_shadow *s)
{
	int i;
	for (i = 0; i < s->req.nr_segments; i++)
		gnttab_end_foreign_access(s->req.seg[i].gref, 0, 0UL);
}