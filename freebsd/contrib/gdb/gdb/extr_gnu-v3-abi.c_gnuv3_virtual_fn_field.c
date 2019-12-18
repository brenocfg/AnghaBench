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
struct type {int dummy; } ;
struct fn_field {int dummy; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_CLASS ; 
 struct type* TYPE_FN_FIELD_FCONTEXT (struct fn_field*,int) ; 
 int /*<<< orphan*/  TYPE_FN_FIELD_TYPE (struct fn_field*,int) ; 
 int /*<<< orphan*/  TYPE_FN_FIELD_VOFFSET (struct fn_field*,int) ; 
 char* TYPE_TAG_NAME (struct type*) ; 
 struct type* TYPE_VPTR_BASETYPE (struct type*) ; 
 scalar_t__ TYPE_VPTR_FIELDNO (struct type*) ; 
 int /*<<< orphan*/  VALUE_BFD_SECTION (struct value*) ; 
 int /*<<< orphan*/  VALUE_TYPE (struct value*) ; 
 int /*<<< orphan*/  builtin_type_int ; 
 struct type* check_typedef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_gdbarch ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  fill_in_vptr_fieldno (struct type*) ; 
 struct type* gdbarch_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct type* lookup_pointer_type (int /*<<< orphan*/ ) ; 
 struct value* value_addr (struct value*) ; 
 scalar_t__ value_as_address (int /*<<< orphan*/ ) ; 
 struct value* value_at_lazy (struct type*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct value* value_cast (struct type*,struct value*) ; 
 int /*<<< orphan*/  value_field (struct value*,scalar_t__) ; 
 int /*<<< orphan*/  value_from_longest (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct value* value_subscript (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vtable_address_point_offset () ; 
 scalar_t__ vtable_field_virtual_functions ; 
 int /*<<< orphan*/  vtable_type_gdbarch_data ; 

__attribute__((used)) static struct value *
gnuv3_virtual_fn_field (struct value **value_p,
                        struct fn_field *f, int j,
			struct type *type, int offset)
{
  struct type *vtable_type = gdbarch_data (current_gdbarch,
					   vtable_type_gdbarch_data);
  struct value *value = *value_p;
  struct type *value_type = check_typedef (VALUE_TYPE (value));
  struct type *vfn_base;
  CORE_ADDR vtable_address;
  struct value *vtable;
  struct value *vfn;

  /* Some simple sanity checks.  */
  if (TYPE_CODE (value_type) != TYPE_CODE_CLASS)
    error ("Only classes can have virtual functions.");

  /* Find the base class that defines this virtual function.  */
  vfn_base = TYPE_FN_FIELD_FCONTEXT (f, j);
  if (! vfn_base)
    /* In programs compiled with G++ version 1, the debug info doesn't
       say which base class defined the virtual function.  We'll guess
       it's the same base class that has our vtable; this is wrong for
       multiple inheritance, but it's better than nothing.  */
    vfn_base = TYPE_VPTR_BASETYPE (type);

  /* This type may have been defined before its virtual function table
     was.  If so, fill in the virtual function table entry for the
     type now.  */
  if (TYPE_VPTR_FIELDNO (vfn_base) < 0)
    fill_in_vptr_fieldno (vfn_base);
  if (TYPE_VPTR_FIELDNO (vfn_base) < 0)
    error ("Could not find virtual table pointer for class \"%s\".",
	   TYPE_TAG_NAME (vfn_base) ? TYPE_TAG_NAME (vfn_base) : "<unknown>");

  /* Now that we know which base class is defining our virtual
     function, cast our value to that baseclass.  This takes care of
     any necessary `this' adjustments.  */
  if (vfn_base != value_type)
    value = value_cast (vfn_base, value);

  /* Now value is an object of the appropriate base type.  Fetch its
     virtual table.  */
  /* It might be possible to do this cast at the same time as the above.
     Does multiple inheritance affect this?
     Can this even trigger, or is TYPE_VPTR_BASETYPE idempotent?
  */
  if (TYPE_VPTR_BASETYPE (vfn_base) != vfn_base)
    value = value_cast (TYPE_VPTR_BASETYPE (vfn_base), value);
  vtable_address
    = value_as_address (value_field (value, TYPE_VPTR_FIELDNO (vfn_base)));

  vtable = value_at_lazy (vtable_type,
                          vtable_address - vtable_address_point_offset (),
                          VALUE_BFD_SECTION (value));

  /* Fetch the appropriate function pointer from the vtable.  */
  vfn = value_subscript (value_field (vtable, vtable_field_virtual_functions),
                         value_from_longest (builtin_type_int,
                                             TYPE_FN_FIELD_VOFFSET (f, j)));

  /* Cast the function pointer to the appropriate type.  */
  vfn = value_cast (lookup_pointer_type (TYPE_FN_FIELD_TYPE (f, j)),
                    vfn);

  /* Is (type)value always numerically the same as (vfn_base)value?
     If so we can spare this cast and use one of the ones above.  */
  *value_p = value_addr (value_cast (type, *value_p));

  return vfn;
}