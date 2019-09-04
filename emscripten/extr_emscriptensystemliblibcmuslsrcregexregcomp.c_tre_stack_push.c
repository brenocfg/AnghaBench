#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  union tre_stack_item {int dummy; } tre_stack_item ;
struct TYPE_3__ {size_t ptr; size_t size; scalar_t__ max_size; int increment; union tre_stack_item* stack; } ;
typedef  TYPE_1__ tre_stack_t ;
typedef  int /*<<< orphan*/  reg_errcode_t ;

/* Variables and functions */
 int /*<<< orphan*/  REG_ESPACE ; 
 int /*<<< orphan*/  REG_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 union tre_stack_item* xrealloc (union tre_stack_item*,int) ; 

__attribute__((used)) static reg_errcode_t
tre_stack_push(tre_stack_t *s, union tre_stack_item value)
{
  if (s->ptr < s->size)
    {
      s->stack[s->ptr] = value;
      s->ptr++;
    }
  else
    {
      if (s->size >= s->max_size)
	{
	  return REG_ESPACE;
	}
      else
	{
	  union tre_stack_item *new_buffer;
	  int new_size;
	  new_size = s->size + s->increment;
	  if (new_size > s->max_size)
	    new_size = s->max_size;
	  new_buffer = xrealloc(s->stack, sizeof(*new_buffer) * new_size);
	  if (new_buffer == NULL)
	    {
	      return REG_ESPACE;
	    }
	  assert(new_size > s->size);
	  s->size = new_size;
	  s->stack = new_buffer;
	  tre_stack_push(s, value);
	}
    }
  return REG_OK;
}