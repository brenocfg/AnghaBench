#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* value_expr_p ;
typedef  int /*<<< orphan*/  temp_expr_table_p ;
struct TYPE_6__ {struct TYPE_6__* next; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 scalar_t__ find_value_in_list (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_value_expr (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static inline void
add_info_to_list (temp_expr_table_p tab, value_expr_p *list, value_expr_p info)
{
  if (find_value_in_list (*list, info->value, NULL))
    free_value_expr (tab, info);
  else
    {
      info->next = *list;
      *list = info;
    }
}