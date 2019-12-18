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
 scalar_t__ TYPE_CODE_STRUCT ; 
 int /*<<< orphan*/  TYPE_TARGET_TYPE (struct type*) ; 
 struct type* check_typedef (int /*<<< orphan*/ ) ; 
 int desc_arity (int /*<<< orphan*/ ) ; 
 struct type* desc_base_type (struct type*) ; 
 int /*<<< orphan*/  desc_bounds_type (struct type*) ; 

int
ada_array_arity (struct type *type)
{
  int arity;

  if (type == NULL)
    return 0;

  type = desc_base_type (type);

  arity = 0;
  if (TYPE_CODE (type) == TYPE_CODE_STRUCT)
    return desc_arity (desc_bounds_type (type));
  else
    while (TYPE_CODE (type) == TYPE_CODE_ARRAY)
      {
	arity += 1;
	type = check_typedef (TYPE_TARGET_TYPE (type));
      }

  return arity;
}