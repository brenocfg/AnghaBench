#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  enum integer_type_kind { ____Placeholder_integer_type_kind } integer_type_kind ;
typedef  int /*<<< orphan*/  cpp_token ;
struct TYPE_7__ {int /*<<< orphan*/  precision; } ;
typedef  TYPE_1__ cpp_options ;
struct TYPE_8__ {int /*<<< orphan*/  high; int /*<<< orphan*/  low; } ;
typedef  TYPE_2__ cpp_num ;

/* Variables and functions */
 unsigned int CPP_N_DECIMAL ; 
 unsigned int CPP_N_IMAGINARY ; 
 unsigned int CPP_N_LARGE ; 
 unsigned int CPP_N_RADIX ; 
 unsigned int CPP_N_UNSIGNED ; 
 unsigned int CPP_N_WIDTH ; 
 int MIN (int,int) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  OPT_Wtraditional ; 
 int /*<<< orphan*/  build_complex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_int_cst (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_int_cst_wide (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* cpp_get_options (int /*<<< orphan*/ ) ; 
 TYPE_2__ cpp_interpret_integer (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 TYPE_2__ cpp_num_sign_extend (TYPE_2__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flag_isoc99 ; 
 int /*<<< orphan*/  in_system_header ; 
 int /*<<< orphan*/ * integer_types ; 
 int itk_long ; 
 int itk_none ; 
 int itk_unsigned_long ; 
 int narrowest_signed_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int narrowest_unsigned_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  parse_in ; 
 int /*<<< orphan*/  pedwarn (char*,char*) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  widest_integer_literal_type_node ; 
 int /*<<< orphan*/  widest_unsigned_literal_type_node ; 

__attribute__((used)) static tree
interpret_integer (const cpp_token *token, unsigned int flags)
{
  tree value, type;
  enum integer_type_kind itk;
  cpp_num integer;
  cpp_options *options = cpp_get_options (parse_in);

  integer = cpp_interpret_integer (parse_in, token, flags);
  integer = cpp_num_sign_extend (integer, options->precision);

  /* The type of a constant with a U suffix is straightforward.  */
  if (flags & CPP_N_UNSIGNED)
    itk = narrowest_unsigned_type (integer.low, integer.high, flags);
  else
    {
      /* The type of a potentially-signed integer constant varies
	 depending on the base it's in, the standard in use, and the
	 length suffixes.  */
      enum integer_type_kind itk_u
	= narrowest_unsigned_type (integer.low, integer.high, flags);
      enum integer_type_kind itk_s
	= narrowest_signed_type (integer.low, integer.high, flags);

      /* In both C89 and C99, octal and hex constants may be signed or
	 unsigned, whichever fits tighter.  We do not warn about this
	 choice differing from the traditional choice, as the constant
	 is probably a bit pattern and either way will work.  */
      if ((flags & CPP_N_RADIX) != CPP_N_DECIMAL)
	itk = MIN (itk_u, itk_s);
      else
	{
	  /* In C99, decimal constants are always signed.
	     In C89, decimal constants that don't fit in long have
	     undefined behavior; we try to make them unsigned long.
	     In GCC's extended C89, that last is true of decimal
	     constants that don't fit in long long, too.  */

	  itk = itk_s;
	  if (itk_s > itk_u && itk_s > itk_long)
	    {
	      if (!flag_isoc99)
		{
		  if (itk_u < itk_unsigned_long)
		    itk_u = itk_unsigned_long;
		  itk = itk_u;
		  warning (0, "this decimal constant is unsigned only in ISO C90");
		}
	      else
		warning (OPT_Wtraditional,
			 "this decimal constant would be unsigned in ISO C90");
	    }
	}
    }

  if (itk == itk_none)
    /* cpplib has already issued a warning for overflow.  */
    type = ((flags & CPP_N_UNSIGNED)
	    ? widest_unsigned_literal_type_node
	    : widest_integer_literal_type_node);
  else
    type = integer_types[itk];

  if (itk > itk_unsigned_long
      && (flags & CPP_N_WIDTH) != CPP_N_LARGE
      && !in_system_header && !flag_isoc99)
    pedwarn ("integer constant is too large for %qs type",
	     (flags & CPP_N_UNSIGNED) ? "unsigned long" : "long");

  value = build_int_cst_wide (type, integer.low, integer.high);

  /* Convert imaginary to a complex type.  */
  if (flags & CPP_N_IMAGINARY)
    value = build_complex (NULL_TREE, build_int_cst (type, 0), value);

  return value;
}