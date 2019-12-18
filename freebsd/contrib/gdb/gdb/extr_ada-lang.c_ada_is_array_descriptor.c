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
 int /*<<< orphan*/  CHECK_TYPEDEF (struct type*) ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_ARRAY ; 
 scalar_t__ TYPE_CODE_PTR ; 
 struct type* TYPE_TARGET_TYPE (struct type*) ; 
 scalar_t__ desc_arity (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  desc_bounds_type (struct type*) ; 
 struct type* desc_data_type (struct type*) ; 

int
ada_is_array_descriptor (struct type *type)
{
  struct type *data_type = desc_data_type (type);

  if (type == NULL)
    return 0;
  CHECK_TYPEDEF (type);
  return
    data_type != NULL
    && ((TYPE_CODE (data_type) == TYPE_CODE_PTR
	 && TYPE_TARGET_TYPE (data_type) != NULL
	 && TYPE_CODE (TYPE_TARGET_TYPE (data_type)) == TYPE_CODE_ARRAY)
	||
	TYPE_CODE (data_type) == TYPE_CODE_ARRAY)
    && desc_arity (desc_bounds_type (type)) > 0;
}