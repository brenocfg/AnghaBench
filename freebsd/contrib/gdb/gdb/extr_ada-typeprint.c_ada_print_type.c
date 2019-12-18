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
struct ui_file {int dummy; } ;
struct type {int dummy; } ;
typedef  enum type_code { ____Placeholder_type_code } type_code ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_TYPEDEF (struct type*) ; 
 int TYPE_CODE (struct type*) ; 
#define  TYPE_CODE_ARRAY 137 
#define  TYPE_CODE_ENUM 136 
#define  TYPE_CODE_FLT 135 
#define  TYPE_CODE_FUNC 134 
#define  TYPE_CODE_INT 133 
#define  TYPE_CODE_PTR 132 
#define  TYPE_CODE_RANGE 131 
#define  TYPE_CODE_REF 130 
#define  TYPE_CODE_STRUCT 129 
#define  TYPE_CODE_UNION 128 
 int /*<<< orphan*/  TYPE_LENGTH (struct type*) ; 
 struct type* TYPE_TARGET_TYPE (struct type*) ; 
 struct type* ada_aligned_type (struct type*) ; 
 struct type* ada_completed_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ada_get_base_type (struct type*) ; 
 scalar_t__ ada_is_aligner_type (struct type*) ; 
 int /*<<< orphan*/  ada_is_array_descriptor (struct type*) ; 
 int /*<<< orphan*/  ada_is_bogus_array_descriptor (struct type*) ; 
 int /*<<< orphan*/  ada_is_fixed_point_type (struct type*) ; 
 int /*<<< orphan*/  ada_is_modular_type (struct type*) ; 
 scalar_t__ ada_is_packed_array_type (struct type*) ; 
 int /*<<< orphan*/  ada_is_range_type_name (char*) ; 
 int /*<<< orphan*/  ada_is_vax_floating_type (struct type*) ; 
 scalar_t__ ada_modulus (struct type*) ; 
 int /*<<< orphan*/  ada_name_prefix_len (char*) ; 
 char* ada_type_name (struct type*) ; 
 int /*<<< orphan*/  c_print_type (struct type*,char*,struct ui_file*,int,int) ; 
 char* demangled_type_name (struct type*) ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,...) ; 
 int /*<<< orphan*/  print_array_type (struct type*,struct ui_file*,int,int) ; 
 int /*<<< orphan*/  print_enum_type (struct type*,struct ui_file*) ; 
 int /*<<< orphan*/  print_fixed_point_type (struct type*,struct ui_file*) ; 
 int /*<<< orphan*/  print_func_type (struct type*,struct ui_file*,char*) ; 
 int /*<<< orphan*/  print_range (struct type*,struct ui_file*) ; 
 int /*<<< orphan*/  print_range_type_named (char*,struct ui_file*) ; 
 int /*<<< orphan*/  print_record_type (struct type*,struct ui_file*,int,int) ; 
 int /*<<< orphan*/  print_unchecked_union_type (struct type*,struct ui_file*,int,int) ; 
 int /*<<< orphan*/  print_vax_floating_point_type (struct type*,struct ui_file*) ; 

void
ada_print_type (struct type *type0, char *varstring, struct ui_file *stream,
		int show, int level)
{
  enum type_code code;
  int demangled_args;
  struct type *type = ada_completed_type (ada_get_base_type (type0));
  char *type_name = demangled_type_name (type);
  int is_var_decl = (varstring != NULL && varstring[0] != '\0');

  if (type == NULL)
    {
      if (is_var_decl)
	fprintf_filtered (stream, "%.*s: ",
			  ada_name_prefix_len (varstring), varstring);
      fprintf_filtered (stream, "<null type?>");
      return;
    }

  if (show > 0)
    CHECK_TYPEDEF (type);

  if (is_var_decl && TYPE_CODE (type) != TYPE_CODE_FUNC)
    fprintf_filtered (stream, "%.*s: ",
		      ada_name_prefix_len (varstring), varstring);

  if (type_name != NULL && show <= 0)
    {
      fprintf_filtered (stream, "%.*s",
			ada_name_prefix_len (type_name), type_name);
      return;
    }

  if (ada_is_aligner_type (type))
    ada_print_type (ada_aligned_type (type), "", stream, show, level);
  else if (ada_is_packed_array_type (type))
    print_array_type (type, stream, show, level);
  else
    switch (TYPE_CODE (type))
      {
      default:
	fprintf_filtered (stream, "<");
	c_print_type (type, "", stream, show, level);
	fprintf_filtered (stream, ">");
	break;
      case TYPE_CODE_PTR:
	fprintf_filtered (stream, "access ");
	ada_print_type (TYPE_TARGET_TYPE (type), "", stream, show, level);
	break;
      case TYPE_CODE_REF:
	fprintf_filtered (stream, "<ref> ");
	ada_print_type (TYPE_TARGET_TYPE (type), "", stream, show, level);
	break;
      case TYPE_CODE_ARRAY:
	print_array_type (type, stream, show, level);
	break;
      case TYPE_CODE_INT:
	if (ada_is_fixed_point_type (type))
	  print_fixed_point_type (type, stream);
	else if (ada_is_vax_floating_type (type))
	  print_vax_floating_point_type (type, stream);
	else
	  {
	    char *name = ada_type_name (type);
	    if (!ada_is_range_type_name (name))
	      fprintf_filtered (stream, "<%d-byte integer>",
				TYPE_LENGTH (type));
	    else
	      {
		fprintf_filtered (stream, "range ");
		print_range_type_named (name, stream);
	      }
	  }
	break;
      case TYPE_CODE_RANGE:
	if (ada_is_fixed_point_type (type))
	  print_fixed_point_type (type, stream);
	else if (ada_is_vax_floating_type (type))
	  print_vax_floating_point_type (type, stream);
	else if (ada_is_modular_type (type))
	  fprintf_filtered (stream, "mod %ld", (long) ada_modulus (type));
	else
	  {
	    fprintf_filtered (stream, "range ");
	    print_range (type, stream);
	  }
	break;
      case TYPE_CODE_FLT:
	fprintf_filtered (stream, "<%d-byte float>", TYPE_LENGTH (type));
	break;
      case TYPE_CODE_ENUM:
	if (show < 0)
	  fprintf_filtered (stream, "(...)");
	else
	  print_enum_type (type, stream);
	break;
      case TYPE_CODE_STRUCT:
	if (ada_is_array_descriptor (type))
	  print_array_type (type, stream, show, level);
	else if (ada_is_bogus_array_descriptor (type))
	  fprintf_filtered (stream,
			    "array (?) of ? (<mal-formed descriptor>)");
	else
	  print_record_type (type, stream, show, level);
	break;
      case TYPE_CODE_UNION:
	print_unchecked_union_type (type, stream, show, level);
	break;
      case TYPE_CODE_FUNC:
	print_func_type (type, stream, varstring);
	break;
      }
}