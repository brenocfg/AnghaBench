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
 scalar_t__ TYPE_CODE_ARRAY ; 
 struct type* TYPE_TARGET_TYPE (struct type*) ; 
 int /*<<< orphan*/  error (char*) ; 

int
calc_f77_array_dims (struct type *array_type)
{
  int ndimen = 1;
  struct type *tmp_type;

  if ((TYPE_CODE (array_type) != TYPE_CODE_ARRAY))
    error ("Can't get dimensions for a non-array type");

  tmp_type = array_type;

  while ((tmp_type = TYPE_TARGET_TYPE (tmp_type)))
    {
      if (TYPE_CODE (tmp_type) == TYPE_CODE_ARRAY)
	++ndimen;
    }
  return ndimen;
}