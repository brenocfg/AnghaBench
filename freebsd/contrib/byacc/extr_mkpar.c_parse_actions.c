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
typedef  int /*<<< orphan*/  action ;

/* Variables and functions */
 int /*<<< orphan*/ * add_reductions (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_shifts (int) ; 

__attribute__((used)) static action *
parse_actions(int stateno)
{
    action *actions;

    actions = get_shifts(stateno);
    actions = add_reductions(stateno, actions);
    return (actions);
}