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
struct minimal_symbol {int dummy; } ;
typedef  int LONGEST ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 char* SYMBOL_DEMANGLED_NAME (struct minimal_symbol*) ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_CLASS ; 
 scalar_t__ TYPE_LENGTH (struct type*) ; 
 char const* TYPE_NAME (struct type*) ; 
 int /*<<< orphan*/  TYPE_VPTR_BASETYPE (struct type*) ; 
 int TYPE_VPTR_FIELDNO (struct type*) ; 
 int VALUE_ADDRESS (struct value*) ; 
 int /*<<< orphan*/  VALUE_BFD_SECTION (struct value*) ; 
 int VALUE_EMBEDDED_OFFSET (struct value*) ; 
 struct type* VALUE_ENCLOSING_TYPE (struct value*) ; 
 int VALUE_OFFSET (struct value*) ; 
 int /*<<< orphan*/  VALUE_TYPE (struct value*) ; 
 struct type* check_typedef (int /*<<< orphan*/ ) ; 
 struct type* cp_lookup_rtti_type (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current_gdbarch ; 
 int /*<<< orphan*/  fill_in_vptr_fieldno (struct type*) ; 
 struct type* gdbarch_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct minimal_symbol* lookup_minimal_symbol_by_pc (int) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 scalar_t__ value_as_address (int /*<<< orphan*/ ) ; 
 int value_as_long (int /*<<< orphan*/ ) ; 
 struct value* value_at_lazy (struct type*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct value* value_cast (struct type*,struct value*) ; 
 int /*<<< orphan*/  value_field (struct value*,int) ; 
 scalar_t__ vtable_address_point_offset () ; 
 int vtable_field_offset_to_top ; 
 int /*<<< orphan*/  vtable_type_gdbarch_data ; 
 int /*<<< orphan*/  warning (char*,char const*) ; 

__attribute__((used)) static struct type *
gnuv3_rtti_type (struct value *value,
                 int *full_p, int *top_p, int *using_enc_p)
{
  struct type *vtable_type = gdbarch_data (current_gdbarch,
					   vtable_type_gdbarch_data);
  struct type *value_type = check_typedef (VALUE_TYPE (value));
  CORE_ADDR vtable_address;
  struct value *vtable;
  struct minimal_symbol *vtable_symbol;
  const char *vtable_symbol_name;
  const char *class_name;
  struct type *run_time_type;
  struct type *base_type;
  LONGEST offset_to_top;

  /* We only have RTTI for class objects.  */
  if (TYPE_CODE (value_type) != TYPE_CODE_CLASS)
    return NULL;

  /* If we can't find the virtual table pointer for value_type, we
     can't find the RTTI.  */
  fill_in_vptr_fieldno (value_type);
  if (TYPE_VPTR_FIELDNO (value_type) == -1)
    return NULL;

  if (using_enc_p)
    *using_enc_p = 0;

  /* Fetch VALUE's virtual table pointer, and tweak it to point at
     an instance of our imaginary gdb_gnu_v3_abi_vtable structure.  */
  base_type = check_typedef (TYPE_VPTR_BASETYPE (value_type));
  if (value_type != base_type)
    {
      value = value_cast (base_type, value);
      if (using_enc_p)
	*using_enc_p = 1;
    }
  vtable_address
    = value_as_address (value_field (value, TYPE_VPTR_FIELDNO (value_type)));
  vtable = value_at_lazy (vtable_type,
                          vtable_address - vtable_address_point_offset (),
                          VALUE_BFD_SECTION (value));
  
  /* Find the linker symbol for this vtable.  */
  vtable_symbol
    = lookup_minimal_symbol_by_pc (VALUE_ADDRESS (vtable)
                                   + VALUE_OFFSET (vtable)
                                   + VALUE_EMBEDDED_OFFSET (vtable));
  if (! vtable_symbol)
    return NULL;
  
  /* The symbol's demangled name should be something like "vtable for
     CLASS", where CLASS is the name of the run-time type of VALUE.
     If we didn't like this approach, we could instead look in the
     type_info object itself to get the class name.  But this way
     should work just as well, and doesn't read target memory.  */
  vtable_symbol_name = SYMBOL_DEMANGLED_NAME (vtable_symbol);
  if (vtable_symbol_name == NULL
      || strncmp (vtable_symbol_name, "vtable for ", 11))
    {
      warning ("can't find linker symbol for virtual table for `%s' value",
	       TYPE_NAME (value_type));
      if (vtable_symbol_name)
	warning ("  found `%s' instead", vtable_symbol_name);
      return NULL;
    }
  class_name = vtable_symbol_name + 11;

  /* Try to look up the class name as a type name.  */
  /* FIXME: chastain/2003-11-26: block=NULL is bogus.  See pr gdb/1465. */
  run_time_type = cp_lookup_rtti_type (class_name, NULL);
  if (run_time_type == NULL)
    return NULL;

  /* Get the offset from VALUE to the top of the complete object.
     NOTE: this is the reverse of the meaning of *TOP_P.  */
  offset_to_top
    = value_as_long (value_field (vtable, vtable_field_offset_to_top));

  if (full_p)
    *full_p = (- offset_to_top == VALUE_EMBEDDED_OFFSET (value)
               && (TYPE_LENGTH (VALUE_ENCLOSING_TYPE (value))
                   >= TYPE_LENGTH (run_time_type)));
  if (top_p)
    *top_p = - offset_to_top;

  return run_time_type;
}