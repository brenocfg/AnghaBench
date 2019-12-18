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
struct c_declspecs {scalar_t__ type; int typespec_word; int default_int_p; scalar_t__ complex_p; scalar_t__ unsigned_p; scalar_t__ signed_p; scalar_t__ short_p; scalar_t__ long_long_p; scalar_t__ long_p; scalar_t__ explicit_signed_p; } ;

/* Variables and functions */
 scalar_t__ NULL_TREE ; 
 scalar_t__ boolean_type_node ; 
 void* build_complex_type (scalar_t__) ; 
 scalar_t__ char_type_node ; 
 scalar_t__ complex_double_type_node ; 
 scalar_t__ complex_float_type_node ; 
 scalar_t__ complex_long_double_type_node ; 
#define  cts_bool 136 
#define  cts_char 135 
#define  cts_dfloat128 134 
#define  cts_dfloat32 133 
#define  cts_dfloat64 132 
#define  cts_double 131 
#define  cts_float 130 
#define  cts_int 129 
 int cts_none ; 
#define  cts_void 128 
 scalar_t__ dfloat128_type_node ; 
 scalar_t__ dfloat32_type_node ; 
 scalar_t__ dfloat64_type_node ; 
 scalar_t__ double_type_node ; 
 scalar_t__ float_type_node ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 scalar_t__ integer_type_node ; 
 scalar_t__ long_double_type_node ; 
 scalar_t__ long_integer_type_node ; 
 scalar_t__ long_long_integer_type_node ; 
 scalar_t__ long_long_unsigned_type_node ; 
 scalar_t__ long_unsigned_type_node ; 
 scalar_t__ pedantic ; 
 int /*<<< orphan*/  pedwarn (char*) ; 
 scalar_t__ short_integer_type_node ; 
 scalar_t__ short_unsigned_type_node ; 
 scalar_t__ signed_char_type_node ; 
 scalar_t__ unsigned_char_type_node ; 
 scalar_t__ unsigned_type_node ; 
 scalar_t__ void_type_node ; 

struct c_declspecs *
finish_declspecs (struct c_declspecs *specs)
{
  /* If a type was specified as a whole, we have no modifiers and are
     done.  */
  if (specs->type != NULL_TREE)
    {
      gcc_assert (!specs->long_p && !specs->long_long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p
		  && !specs->complex_p);
      return specs;
    }

  /* If none of "void", "_Bool", "char", "int", "float" or "double"
     has been specified, treat it as "int" unless "_Complex" is
     present and there are no other specifiers.  If we just have
     "_Complex", it is equivalent to "_Complex double", but e.g.
     "_Complex short" is equivalent to "_Complex short int".  */
  if (specs->typespec_word == cts_none)
    {
      if (specs->long_p || specs->short_p
	  || specs->signed_p || specs->unsigned_p)
	{
	  specs->typespec_word = cts_int;
	}
      else if (specs->complex_p)
	{
	  specs->typespec_word = cts_double;
	  if (pedantic)
	    pedwarn ("ISO C does not support plain %<complex%> meaning "
		     "%<double complex%>");
	}
      else
	{
	  specs->typespec_word = cts_int;
	  specs->default_int_p = true;
	  /* We don't diagnose this here because grokdeclarator will
	     give more specific diagnostics according to whether it is
	     a function definition.  */
	}
    }

  /* If "signed" was specified, record this to distinguish "int" and
     "signed int" in the case of a bit-field with
     -funsigned-bitfields.  */
  specs->explicit_signed_p = specs->signed_p;

  /* Now compute the actual type.  */
  switch (specs->typespec_word)
    {
    case cts_void:
      gcc_assert (!specs->long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p
		  && !specs->complex_p);
      specs->type = void_type_node;
      break;
    case cts_bool:
      gcc_assert (!specs->long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p
		  && !specs->complex_p);
      specs->type = boolean_type_node;
      break;
    case cts_char:
      gcc_assert (!specs->long_p && !specs->short_p);
      gcc_assert (!(specs->signed_p && specs->unsigned_p));
      if (specs->signed_p)
	specs->type = signed_char_type_node;
      else if (specs->unsigned_p)
	specs->type = unsigned_char_type_node;
      else
	specs->type = char_type_node;
      if (specs->complex_p)
	{
	  if (pedantic)
	    pedwarn ("ISO C does not support complex integer types");
	  specs->type = build_complex_type (specs->type);
	}
      break;
    case cts_int:
      gcc_assert (!(specs->long_p && specs->short_p));
      gcc_assert (!(specs->signed_p && specs->unsigned_p));
      if (specs->long_long_p)
	specs->type = (specs->unsigned_p
		       ? long_long_unsigned_type_node
		       : long_long_integer_type_node);
      else if (specs->long_p)
	specs->type = (specs->unsigned_p
		       ? long_unsigned_type_node
		       : long_integer_type_node);
      else if (specs->short_p)
	specs->type = (specs->unsigned_p
		       ? short_unsigned_type_node
		       : short_integer_type_node);
      else
	specs->type = (specs->unsigned_p
		       ? unsigned_type_node
		       : integer_type_node);
      if (specs->complex_p)
	{
	  if (pedantic)
	    pedwarn ("ISO C does not support complex integer types");
	  specs->type = build_complex_type (specs->type);
	}
      break;
    case cts_float:
      gcc_assert (!specs->long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p);
      specs->type = (specs->complex_p
		     ? complex_float_type_node
		     : float_type_node);
      break;
    case cts_double:
      gcc_assert (!specs->long_long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p);
      if (specs->long_p)
	{
	  specs->type = (specs->complex_p
			 ? complex_long_double_type_node
			 : long_double_type_node);
	}
      else
	{
	  specs->type = (specs->complex_p
			 ? complex_double_type_node
			 : double_type_node);
	}
      break;
    case cts_dfloat32:
    case cts_dfloat64:
    case cts_dfloat128:
      gcc_assert (!specs->long_p && !specs->long_long_p && !specs->short_p
		  && !specs->signed_p && !specs->unsigned_p && !specs->complex_p);
      if (specs->typespec_word == cts_dfloat32)
	specs->type = dfloat32_type_node;
      else if (specs->typespec_word == cts_dfloat64)
	specs->type = dfloat64_type_node;
      else
	specs->type = dfloat128_type_node;
      break;
    default:
      gcc_unreachable ();
    }

  return specs;
}