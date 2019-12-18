#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* value_expr_p ;
struct TYPE_7__ {struct TYPE_7__* next; } ;

/* Variables and functions */
 TYPE_1__* find_value_in_list (TYPE_1__*,int,TYPE_1__**) ; 

__attribute__((used)) static value_expr_p
remove_value_from_list (value_expr_p *list, int value)
{
  value_expr_p info, last;

  info = find_value_in_list (*list, value, &last);
  if (!info)
    return NULL;
  if (!last)
    *list = info->next;
  else
    last->next = info->next;
 
  return info;
}