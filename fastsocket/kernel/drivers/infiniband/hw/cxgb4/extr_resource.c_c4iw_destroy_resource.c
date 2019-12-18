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
struct c4iw_resource {int /*<<< orphan*/  pdid_table; int /*<<< orphan*/  qid_table; int /*<<< orphan*/  tpt_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  c4iw_id_table_free (int /*<<< orphan*/ *) ; 

void c4iw_destroy_resource(struct c4iw_resource *rscp)
{
	c4iw_id_table_free(&rscp->tpt_table);
	c4iw_id_table_free(&rscp->qid_table);
	c4iw_id_table_free(&rscp->pdid_table);
}