#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* value_set_t ;
typedef  TYPE_2__* value_set_node_t ;
struct TYPE_7__ {int /*<<< orphan*/  expr; struct TYPE_7__* next; } ;
struct TYPE_6__ {scalar_t__ length; TYPE_2__* head; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_value_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_contains_value (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
set_equal (value_set_t a, value_set_t b)
{
  value_set_node_t node;

  if (a->length != b->length)
    return false;
  for (node = a->head;
       node;
       node = node->next)
    {
      if (!set_contains_value (b, get_value_handle (node->expr)))
	return false;
    }
  return true;
}