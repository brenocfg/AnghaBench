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
struct ro_spine {int /*<<< orphan*/ ** nodes; scalar_t__ count; struct dm_btree_info* info; } ;
struct dm_btree_info {int dummy; } ;

/* Variables and functions */

void init_ro_spine(struct ro_spine *s, struct dm_btree_info *info)
{
	s->info = info;
	s->count = 0;
	s->nodes[0] = NULL;
	s->nodes[1] = NULL;
}