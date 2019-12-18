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
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BASETYPE_VIA_VIRTUAL (struct type*,int) ; 
 int TYPE_BASECLASS_BITPOS (struct type*,int) ; 
 scalar_t__ TYPE_FIELD_BITPOS (struct type*,scalar_t__) ; 
 long TYPE_LENGTH (struct type*) ; 
 char* TYPE_NAME (struct type*) ; 
 struct type* TYPE_VPTR_BASETYPE (struct type*) ; 
 scalar_t__ TYPE_VPTR_FIELDNO (struct type*) ; 
 int /*<<< orphan*/  builtin_type_int ; 
 struct type* builtin_type_void_data_ptr ; 
 int /*<<< orphan*/  current_gdbarch ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  fill_in_vptr_fieldno (struct type*) ; 
 struct type* gdbarch_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ value_as_address (struct value*) ; 
 long value_as_long (int /*<<< orphan*/ ) ; 
 struct value* value_at_lazy (struct type*,scalar_t__,int /*<<< orphan*/ *) ; 
 struct value* value_field (struct value*,int /*<<< orphan*/ ) ; 
 struct value* value_from_longest (int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  value_subscript (struct value*,struct value*) ; 
 long vtable_address_point_offset () ; 
 int /*<<< orphan*/  vtable_field_vcall_and_vbase_offsets ; 
 int /*<<< orphan*/  vtable_type_gdbarch_data ; 

__attribute__((used)) static int
gnuv3_baseclass_offset (struct type *type, int index, char *valaddr,
			CORE_ADDR address)
{
  struct type *vtable_type = gdbarch_data (current_gdbarch,
					   vtable_type_gdbarch_data);
  struct value *vtable;
  struct type *vbasetype;
  struct value *offset_val, *vbase_array;
  CORE_ADDR vtable_address;
  long int cur_base_offset, base_offset;

  /* If it isn't a virtual base, this is easy.  The offset is in the
     type definition.  */
  if (!BASETYPE_VIA_VIRTUAL (type, index))
    return TYPE_BASECLASS_BITPOS (type, index) / 8;

  /* To access a virtual base, we need to use the vbase offset stored in
     our vtable.  Recent GCC versions provide this information.  If it isn't
     available, we could get what we needed from RTTI, or from drawing the
     complete inheritance graph based on the debug info.  Neither is
     worthwhile.  */
  cur_base_offset = TYPE_BASECLASS_BITPOS (type, index) / 8;
  if (cur_base_offset >= - vtable_address_point_offset ())
    error ("Expected a negative vbase offset (old compiler?)");

  cur_base_offset = cur_base_offset + vtable_address_point_offset ();
  if ((- cur_base_offset) % TYPE_LENGTH (builtin_type_void_data_ptr) != 0)
    error ("Misaligned vbase offset.");
  cur_base_offset = cur_base_offset
    / ((int) TYPE_LENGTH (builtin_type_void_data_ptr));

  /* We're now looking for the cur_base_offset'th entry (negative index)
     in the vcall_and_vbase_offsets array.  We used to cast the object to
     its TYPE_VPTR_BASETYPE, and reference the vtable as TYPE_VPTR_FIELDNO;
     however, that cast can not be done without calling baseclass_offset again
     if the TYPE_VPTR_BASETYPE is a virtual base class, as described in the
     v3 C++ ABI Section 2.4.I.2.b.  Fortunately the ABI guarantees that the
     vtable pointer will be located at the beginning of the object, so we can
     bypass the casting.  Verify that the TYPE_VPTR_FIELDNO is in fact at the
     start of whichever baseclass it resides in, as a sanity measure - iff
     we have debugging information for that baseclass.  */

  vbasetype = TYPE_VPTR_BASETYPE (type);
  if (TYPE_VPTR_FIELDNO (vbasetype) < 0)
    fill_in_vptr_fieldno (vbasetype);

  if (TYPE_VPTR_FIELDNO (vbasetype) >= 0
      && TYPE_FIELD_BITPOS (vbasetype, TYPE_VPTR_FIELDNO (vbasetype)) != 0)
    error ("Illegal vptr offset in class %s",
	   TYPE_NAME (vbasetype) ? TYPE_NAME (vbasetype) : "<unknown>");

  vtable_address = value_as_address (value_at_lazy (builtin_type_void_data_ptr,
						    address, NULL));
  vtable = value_at_lazy (vtable_type,
                          vtable_address - vtable_address_point_offset (),
                          NULL);
  offset_val = value_from_longest(builtin_type_int, cur_base_offset);
  vbase_array = value_field (vtable, vtable_field_vcall_and_vbase_offsets);
  base_offset = value_as_long (value_subscript (vbase_array, offset_val));
  return base_offset;
}