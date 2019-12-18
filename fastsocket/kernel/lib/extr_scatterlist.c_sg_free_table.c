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
struct sg_table {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SG_MAX_SINGLE_ALLOC ; 
 int /*<<< orphan*/  __sg_free_table (struct sg_table*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_kfree ; 

void sg_free_table(struct sg_table *table)
{
	__sg_free_table(table, SG_MAX_SINGLE_ALLOC, sg_kfree);
}