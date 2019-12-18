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
 struct type* TYPE_FIELD_TYPE (struct type*,int /*<<< orphan*/ ) ; 
 struct type* TYPE_TARGET_TYPE (struct type*) ; 
 int ada_array_arity (struct type*) ; 
 scalar_t__ ada_is_simple_array (struct type*) ; 
 struct type* desc_base_type (struct type*) ; 
 int /*<<< orphan*/  desc_bounds_type (struct type*) ; 
 struct type* desc_index_type (int /*<<< orphan*/ ,int) ; 

struct type *
ada_index_type (struct type *type, int n)
{
  type = desc_base_type (type);

  if (n > ada_array_arity (type))
    return NULL;

  if (ada_is_simple_array (type))
    {
      int i;

      for (i = 1; i < n; i += 1)
	type = TYPE_TARGET_TYPE (type);

      return TYPE_TARGET_TYPE (TYPE_FIELD_TYPE (type, 0));
    }
  else
    return desc_index_type (desc_bounds_type (type), n);
}