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
typedef  TYPE_1__* value_expr_p ;
typedef  int /*<<< orphan*/  temp_expr_table_p ;
struct TYPE_5__ {int value; struct TYPE_5__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  find_value_in_list (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 TYPE_1__* new_value_expr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
add_value_to_list (temp_expr_table_p tab, value_expr_p *list, int value)
{
  value_expr_p info;

  if (!find_value_in_list (*list, value, NULL))
    {
      info = new_value_expr (tab);
      info->value = value;
      info->next = *list;
      *list = info;
    }
}