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
struct table {int /*<<< orphan*/ * table; scalar_t__ nentry; scalar_t__ offset_max; int /*<<< orphan*/  offsets; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void table_init(struct table *t)
{
	INIT_LIST_HEAD(&t->offsets);
	t->offset_max = 0;
	t->nentry = 0;
	t->table = NULL;
}