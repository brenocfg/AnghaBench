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
struct type {int dummy; } ;

/* Variables and functions */
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_CLASS ; 
 struct type** virtual_base_list (struct type*) ; 

int
virtual_base_index (struct type *base, struct type *dclass)
{
  struct type *vbase;
  int i;

  if ((TYPE_CODE (dclass) != TYPE_CODE_CLASS) ||
      (TYPE_CODE (base) != TYPE_CODE_CLASS))
    return -1;

  i = 0;
  vbase = virtual_base_list (dclass)[0];
  while (vbase)
    {
      if (vbase == base)
	break;
      vbase = virtual_base_list (dclass)[++i];
    }

  return vbase ? i : -1;
}