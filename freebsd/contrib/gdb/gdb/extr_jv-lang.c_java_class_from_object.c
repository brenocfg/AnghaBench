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
struct value {int dummy; } ;

/* Variables and functions */
 scalar_t__ TYPE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_CODE_PTR ; 
 scalar_t__ TYPE_LENGTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_TARGET_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VALUE_TYPE (struct value*) ; 
 int /*<<< orphan*/  get_java_object_type () ; 
 int /*<<< orphan*/  value_as_address (struct value*) ; 
 struct value* value_at (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct value* value_struct_elt (struct value**,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char*) ; 

struct value *
java_class_from_object (struct value *obj_val)
{
  /* This is all rather inefficient, since the offsets of vtable and
     class are fixed.  FIXME */
  struct value *vtable_val;

  if (TYPE_CODE (VALUE_TYPE (obj_val)) == TYPE_CODE_PTR
      && TYPE_LENGTH (TYPE_TARGET_TYPE (VALUE_TYPE (obj_val))) == 0)
    obj_val = value_at (get_java_object_type (),
			value_as_address (obj_val), NULL);

  vtable_val = value_struct_elt (&obj_val, NULL, "vtable", NULL, "structure");
  return value_struct_elt (&vtable_val, NULL, "class", NULL, "structure");
}