#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_2__ {int /*<<< orphan*/  type; scalar_t__ hidden; } ;

/* Variables and functions */
 int current_class_depth ; 
 TYPE_1__* current_class_stack ; 
 int /*<<< orphan*/  current_class_type ; 
 scalar_t__ same_type_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
currently_open_class (tree t)
{
  int i;

  /* We start looking from 1 because entry 0 is from global scope,
     and has no type.  */
  for (i = current_class_depth; i > 0; --i)
    {
      tree c;
      if (i == current_class_depth)
	c = current_class_type;
      else
	{
	  if (current_class_stack[i].hidden)
	    break;
	  c = current_class_stack[i].type;
	}
      if (!c)
	continue;
      if (same_type_p (c, t))
	return true;
    }
  return false;
}