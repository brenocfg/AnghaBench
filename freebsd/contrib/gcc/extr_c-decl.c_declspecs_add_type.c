#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  char const* tree ;
struct c_typespec {char* spec; scalar_t__ kind; } ;
struct c_declspecs {int non_sc_seen_p; int declspecs_seen_p; int type_seen_p; int deprecated_p; int unavailable_p; char const* type; int long_long_p; int long_p; scalar_t__ typespec_word; int short_p; int signed_p; int unsigned_p; int complex_p; int typedef_p; int tag_defined_p; int /*<<< orphan*/  explicit_signed_p; int /*<<< orphan*/  decl_attr; } ;
typedef  enum rid { ____Placeholder_rid } rid ;
struct TYPE_2__ {int /*<<< orphan*/  (* decimal_float_supported_p ) () ;} ;

/* Variables and functions */
 scalar_t__ C_IS_RESERVED_WORD (char const*) ; 
 int C_RID_CODE (char const*) ; 
 int /*<<< orphan*/  C_TYPEDEF_EXPLICITLY_SIGNED (char const*) ; 
 int /*<<< orphan*/  DECL_ATTRIBUTES (char const*) ; 
 scalar_t__ ERROR_MARK ; 
 scalar_t__ IDENTIFIER_NODE ; 
#define  RID_BOOL 141 
#define  RID_CHAR 140 
#define  RID_COMPLEX 139 
#define  RID_DFLOAT128 138 
#define  RID_DFLOAT32 137 
#define  RID_DFLOAT64 136 
#define  RID_DOUBLE 135 
#define  RID_FLOAT 134 
#define  RID_INT 133 
 scalar_t__ RID_LAST_MODIFIER ; 
#define  RID_LONG 132 
#define  RID_SHORT 131 
#define  RID_SIGNED 130 
#define  RID_UNSIGNED 129 
#define  RID_VOID 128 
 scalar_t__ TREE_CODE (char const*) ; 
 scalar_t__ TREE_DEPRECATED (char const*) ; 
 scalar_t__ TREE_TYPE (char const*) ; 
 scalar_t__ TREE_UNAVAILABLE (char const*) ; 
 scalar_t__ TYPE_DECL ; 
 scalar_t__ cts_bool ; 
 scalar_t__ cts_char ; 
 scalar_t__ cts_dfloat128 ; 
 scalar_t__ cts_dfloat32 ; 
 scalar_t__ cts_dfloat64 ; 
 scalar_t__ cts_double ; 
 scalar_t__ cts_float ; 
 scalar_t__ cts_int ; 
 scalar_t__ cts_none ; 
 scalar_t__ cts_void ; 
 scalar_t__ ctsk_tagdef ; 
 scalar_t__ ctsk_tagfirstref ; 
 scalar_t__ ctsk_typeof ; 
 int /*<<< orphan*/  error (char*,...) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  flag_isoc99 ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  in_system_header ; 
 char* lookup_name (char const*) ; 
 int /*<<< orphan*/  pedantic ; 
 int /*<<< orphan*/  pedwarn (char*) ; 
 int /*<<< orphan*/  stub1 () ; 
 TYPE_1__ targetm ; 
 int /*<<< orphan*/  warn_long_long ; 

struct c_declspecs *
declspecs_add_type (struct c_declspecs *specs, struct c_typespec spec)
{
  tree type = spec.spec;
  specs->non_sc_seen_p = true;
  specs->declspecs_seen_p = true;
  specs->type_seen_p = true;
  if (TREE_DEPRECATED (type))
    specs->deprecated_p = true;

  /* APPLE LOCAL begin "unavailable" attribute (radar 2809697) */
  if (TREE_UNAVAILABLE (type))
    specs->unavailable_p = true;
  /* APPLE LOCAL end "unavailable" attribute (radar 2809697) */

  /* Handle type specifier keywords.  */
  if (TREE_CODE (type) == IDENTIFIER_NODE && C_IS_RESERVED_WORD (type))
    {
      enum rid i = C_RID_CODE (type);
      if (specs->type)
	{
	  error ("two or more data types in declaration specifiers");
	  return specs;
	}
      if ((int) i <= (int) RID_LAST_MODIFIER)
	{
	  /* "long", "short", "signed", "unsigned" or "_Complex".  */
	  bool dupe = false;
	  switch (i)
	    {
	    case RID_LONG:
	      if (specs->long_long_p)
		{
		  error ("%<long long long%> is too long for GCC");
		  break;
		}
	      if (specs->long_p)
		{
		  if (specs->typespec_word == cts_double)
		    {
		      error ("both %<long long%> and %<double%> in "
			     "declaration specifiers");
		      break;
		    }
		  if (pedantic && !flag_isoc99 && !in_system_header
		      && warn_long_long)
		    pedwarn ("ISO C90 does not support %<long long%>");
		  specs->long_long_p = 1;
		  break;
		}
	      if (specs->short_p)
		error ("both %<long%> and %<short%> in "
		       "declaration specifiers");
	      else if (specs->typespec_word == cts_void)
		error ("both %<long%> and %<void%> in "
		       "declaration specifiers");
	      else if (specs->typespec_word == cts_bool)
		error ("both %<long%> and %<_Bool%> in "
		       "declaration specifiers");
	      else if (specs->typespec_word == cts_char)
		error ("both %<long%> and %<char%> in "
		       "declaration specifiers");
	      else if (specs->typespec_word == cts_float)
		error ("both %<long%> and %<float%> in "
		       "declaration specifiers");
	      else if (specs->typespec_word == cts_dfloat32)
		error ("both %<long%> and %<_Decimal32%> in "
		       "declaration specifiers");
	      else if (specs->typespec_word == cts_dfloat64)
		error ("both %<long%> and %<_Decimal64%> in "
		       "declaration specifiers");
	      else if (specs->typespec_word == cts_dfloat128)
		error ("both %<long%> and %<_Decimal128%> in "
		       "declaration specifiers");
	      else
		specs->long_p = true;
	      break;
	    case RID_SHORT:
	      dupe = specs->short_p;
	      if (specs->long_p)
		error ("both %<long%> and %<short%> in "
		       "declaration specifiers");
	      else if (specs->typespec_word == cts_void)
		error ("both %<short%> and %<void%> in "
		       "declaration specifiers");
	      else if (specs->typespec_word == cts_bool)
		error ("both %<short%> and %<_Bool%> in "
		       "declaration specifiers");
	      else if (specs->typespec_word == cts_char)
		error ("both %<short%> and %<char%> in "
		       "declaration specifiers");
	      else if (specs->typespec_word == cts_float)
		error ("both %<short%> and %<float%> in "
		       "declaration specifiers");
	      else if (specs->typespec_word == cts_double)
		error ("both %<short%> and %<double%> in "
		       "declaration specifiers");
	      else if (specs->typespec_word == cts_dfloat32)
                error ("both %<short%> and %<_Decimal32%> in "
		       "declaration specifiers");
	      else if (specs->typespec_word == cts_dfloat64)
		error ("both %<short%> and %<_Decimal64%> in "
		                        "declaration specifiers");
	      else if (specs->typespec_word == cts_dfloat128)
		error ("both %<short%> and %<_Decimal128%> in "
		       "declaration specifiers");
	      else
		specs->short_p = true;
	      break;
	    case RID_SIGNED:
	      dupe = specs->signed_p;
	      if (specs->unsigned_p)
		error ("both %<signed%> and %<unsigned%> in "
		       "declaration specifiers");
	      else if (specs->typespec_word == cts_void)
		error ("both %<signed%> and %<void%> in "
		       "declaration specifiers");
	      else if (specs->typespec_word == cts_bool)
		error ("both %<signed%> and %<_Bool%> in "
		       "declaration specifiers");
	      else if (specs->typespec_word == cts_float)
		error ("both %<signed%> and %<float%> in "
		       "declaration specifiers");
	      else if (specs->typespec_word == cts_double)
		error ("both %<signed%> and %<double%> in "
		       "declaration specifiers");
	      else if (specs->typespec_word == cts_dfloat32)
		error ("both %<signed%> and %<_Decimal32%> in "
		       "declaration specifiers");
	      else if (specs->typespec_word == cts_dfloat64)
		error ("both %<signed%> and %<_Decimal64%> in "
		       "declaration specifiers");
	      else if (specs->typespec_word == cts_dfloat128)
		error ("both %<signed%> and %<_Decimal128%> in "
		       "declaration specifiers");
	      else
		specs->signed_p = true;
	      break;
	    case RID_UNSIGNED:
	      dupe = specs->unsigned_p;
	      if (specs->signed_p)
		error ("both %<signed%> and %<unsigned%> in "
		       "declaration specifiers");
	      else if (specs->typespec_word == cts_void)
		error ("both %<unsigned%> and %<void%> in "
		       "declaration specifiers");
	      else if (specs->typespec_word == cts_bool)
		error ("both %<unsigned%> and %<_Bool%> in "
		       "declaration specifiers");
	      else if (specs->typespec_word == cts_float)
		error ("both %<unsigned%> and %<float%> in "
		       "declaration specifiers");
	      else if (specs->typespec_word == cts_double)
		error ("both %<unsigned%> and %<double%> in "
		       "declaration specifiers");
              else if (specs->typespec_word == cts_dfloat32)
		error ("both %<unsigned%> and %<_Decimal32%> in "
		       "declaration specifiers");
	      else if (specs->typespec_word == cts_dfloat64)
		error ("both %<unsigned%> and %<_Decimal64%> in "
		       "declaration specifiers");
	      else if (specs->typespec_word == cts_dfloat128)
		error ("both %<unsigned%> and %<_Decimal128%> in "
		       "declaration specifiers");
	      else
		specs->unsigned_p = true;
	      break;
	    case RID_COMPLEX:
	      dupe = specs->complex_p;
	      if (pedantic && !flag_isoc99 && !in_system_header)
		pedwarn ("ISO C90 does not support complex types");
	      if (specs->typespec_word == cts_void)
		error ("both %<complex%> and %<void%> in "
		       "declaration specifiers");
	      else if (specs->typespec_word == cts_bool)
		error ("both %<complex%> and %<_Bool%> in "
		       "declaration specifiers");
              else if (specs->typespec_word == cts_dfloat32)
		error ("both %<complex%> and %<_Decimal32%> in "
		       "declaration specifiers");
	      else if (specs->typespec_word == cts_dfloat64)
		error ("both %<complex%> and %<_Decimal64%> in "
		       "declaration specifiers");
	      else if (specs->typespec_word == cts_dfloat128)
		error ("both %<complex%> and %<_Decimal128%> in "
		       "declaration specifiers");
	      else
		specs->complex_p = true;
	      break;
	    default:
	      gcc_unreachable ();
	    }

	  if (dupe)
	    error ("duplicate %qE", type);

	  return specs;
	}
      else
	{
	  /* "void", "_Bool", "char", "int", "float" or "double".  */
	  if (specs->typespec_word != cts_none)
	    {
	      error ("two or more data types in declaration specifiers");
	      return specs;
	    }
	  switch (i)
	    {
	    case RID_VOID:
	      if (specs->long_p)
		error ("both %<long%> and %<void%> in "
		       "declaration specifiers");
	      else if (specs->short_p)
		error ("both %<short%> and %<void%> in "
		       "declaration specifiers");
	      else if (specs->signed_p)
		error ("both %<signed%> and %<void%> in "
		       "declaration specifiers");
	      else if (specs->unsigned_p)
		error ("both %<unsigned%> and %<void%> in "
		       "declaration specifiers");
	      else if (specs->complex_p)
		error ("both %<complex%> and %<void%> in "
		       "declaration specifiers");
	      else
		specs->typespec_word = cts_void;
	      return specs;
	    case RID_BOOL:
	      if (specs->long_p)
		error ("both %<long%> and %<_Bool%> in "
		       "declaration specifiers");
	      else if (specs->short_p)
		error ("both %<short%> and %<_Bool%> in "
		       "declaration specifiers");
	      else if (specs->signed_p)
		error ("both %<signed%> and %<_Bool%> in "
		       "declaration specifiers");
	      else if (specs->unsigned_p)
		error ("both %<unsigned%> and %<_Bool%> in "
		       "declaration specifiers");
	      else if (specs->complex_p)
		error ("both %<complex%> and %<_Bool%> in "
		       "declaration specifiers");
	      else
		specs->typespec_word = cts_bool;
	      return specs;
	    case RID_CHAR:
	      if (specs->long_p)
		error ("both %<long%> and %<char%> in "
		       "declaration specifiers");
	      else if (specs->short_p)
		error ("both %<short%> and %<char%> in "
		       "declaration specifiers");
	      else
		specs->typespec_word = cts_char;
	      return specs;
	    case RID_INT:
	      specs->typespec_word = cts_int;
	      return specs;
	    case RID_FLOAT:
	      if (specs->long_p)
		error ("both %<long%> and %<float%> in "
		       "declaration specifiers");
	      else if (specs->short_p)
		error ("both %<short%> and %<float%> in "
		       "declaration specifiers");
	      else if (specs->signed_p)
		error ("both %<signed%> and %<float%> in "
		       "declaration specifiers");
	      else if (specs->unsigned_p)
		error ("both %<unsigned%> and %<float%> in "
		       "declaration specifiers");
	      else
		specs->typespec_word = cts_float;
	      return specs;
	    case RID_DOUBLE:
	      if (specs->long_long_p)
		error ("both %<long long%> and %<double%> in "
		       "declaration specifiers");
	      else if (specs->short_p)
		error ("both %<short%> and %<double%> in "
		       "declaration specifiers");
	      else if (specs->signed_p)
		error ("both %<signed%> and %<double%> in "
		       "declaration specifiers");
	      else if (specs->unsigned_p)
		error ("both %<unsigned%> and %<double%> in "
		       "declaration specifiers");
	      else
		specs->typespec_word = cts_double;
	      return specs;
	    case RID_DFLOAT32:
	    case RID_DFLOAT64:
	    case RID_DFLOAT128:
	      { 
		const char *str;
		if (i == RID_DFLOAT32)
		  str = "_Decimal32";
		else if (i == RID_DFLOAT64)
		  str = "_Decimal64";
		else
		  str = "_Decimal128";
		if (specs->long_long_p)
		  error ("both %<long long%> and %<%s%> in "
			 "declaration specifiers", str);
		if (specs->long_p)
		  error ("both %<long%> and %<%s%> in "
			 "declaration specifiers", str);
		else if (specs->short_p)
		  error ("both %<short%> and %<%s%> in "
			 "declaration specifiers", str);
		else if (specs->signed_p)
		  error ("both %<signed%> and %<%s%> in "
			 "declaration specifiers", str);
		else if (specs->unsigned_p)
		  error ("both %<unsigned%> and %<%s%> in "
			 "declaration specifiers", str);
                else if (specs->complex_p)
                  error ("both %<complex%> and %<%s%> in "
                         "declaration specifiers", str);
		else if (i == RID_DFLOAT32)
		  specs->typespec_word = cts_dfloat32;
		else if (i == RID_DFLOAT64)
		  specs->typespec_word = cts_dfloat64;
		else
		  specs->typespec_word = cts_dfloat128;
	      }
	      if (!targetm.decimal_float_supported_p ())
		error ("decimal floating point not supported for this target");
	      if (pedantic)
		pedwarn ("ISO C does not support decimal floating point");
	      return specs;
	    default:
	      /* ObjC reserved word "id", handled below.  */
	      break;
	    }
	}
    }

  /* Now we have a typedef (a TYPE_DECL node), an identifier (some
     form of ObjC type, cases such as "int" and "long" being handled
     above), a TYPE (struct, union, enum and typeof specifiers) or an
     ERROR_MARK.  In none of these cases may there have previously
     been any type specifiers.  */
  if (specs->type || specs->typespec_word != cts_none
      || specs->long_p || specs->short_p || specs->signed_p
      || specs->unsigned_p || specs->complex_p)
    error ("two or more data types in declaration specifiers");
  else if (TREE_CODE (type) == TYPE_DECL)
    {
      if (TREE_TYPE (type) == error_mark_node)
	; /* Allow the type to default to int to avoid cascading errors.  */
      else
	{
	  specs->type = TREE_TYPE (type);
	  specs->decl_attr = DECL_ATTRIBUTES (type);
	  specs->typedef_p = true;
	  specs->explicit_signed_p = C_TYPEDEF_EXPLICITLY_SIGNED (type);
	}
    }
  else if (TREE_CODE (type) == IDENTIFIER_NODE)
    {
      tree t = lookup_name (type);
      if (!t || TREE_CODE (t) != TYPE_DECL)
	error ("%qE fails to be a typedef or built in type", type);
      else if (TREE_TYPE (t) == error_mark_node)
	;
      else
	specs->type = TREE_TYPE (t);
    }
  else if (TREE_CODE (type) != ERROR_MARK)
    {
      if (spec.kind == ctsk_tagdef || spec.kind == ctsk_tagfirstref)
	specs->tag_defined_p = true;
      if (spec.kind == ctsk_typeof)
	specs->typedef_p = true;
      specs->type = type;
    }

  return specs;
}