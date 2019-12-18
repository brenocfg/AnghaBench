#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int dtsp_num_conditions; } ;
typedef  TYPE_1__ dt_sugar_parse_t ;
typedef  int /*<<< orphan*/  dt_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  dt_sugar_append_clause (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_sugar_new_condition_impl (TYPE_1__*,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int
dt_sugar_new_condition(dt_sugar_parse_t *dp, dt_node_t *pred, int condid)
{
	dp->dtsp_num_conditions++;
	dt_sugar_append_clause(dp, dt_sugar_new_condition_impl(dp,
	    pred, condid, dp->dtsp_num_conditions));
	return (dp->dtsp_num_conditions);
}