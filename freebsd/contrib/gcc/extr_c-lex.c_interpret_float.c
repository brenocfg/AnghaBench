#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_5__ {size_t len; int /*<<< orphan*/  text; } ;
struct TYPE_6__ {TYPE_1__ str; } ;
struct TYPE_7__ {TYPE_2__ val; } ;
typedef  TYPE_3__ cpp_token ;
typedef  int /*<<< orphan*/  REAL_VALUE_TYPE ;

/* Variables and functions */
 unsigned int CPP_N_DEFAULT ; 
 unsigned int CPP_N_DFLOAT ; 
 unsigned int CPP_N_IMAGINARY ; 
 unsigned int CPP_N_LARGE ; 
 unsigned int CPP_N_MEDIUM ; 
 unsigned int CPP_N_SMALL ; 
 unsigned int CPP_N_WIDTH ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ REAL_VALUE_ISINF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ alloca (size_t) ; 
 int /*<<< orphan*/  build_complex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_real (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dfloat128_type_node ; 
 int /*<<< orphan*/  dfloat32_type_node ; 
 int /*<<< orphan*/  dfloat64_type_node ; 
 int /*<<< orphan*/  double_type_node ; 
 scalar_t__ flag_single_precision_constant ; 
 int /*<<< orphan*/  float_type_node ; 
 int /*<<< orphan*/  integer_zero_node ; 
 int /*<<< orphan*/  long_double_type_node ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ pedantic ; 
 int /*<<< orphan*/  pedwarn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  real_from_string3 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
interpret_float (const cpp_token *token, unsigned int flags)
{
  tree type;
  tree value;
  REAL_VALUE_TYPE real;
  char *copy;
  size_t copylen;

  /* Default (no suffix) is double.  */
  if (flags & CPP_N_DEFAULT)
    {
      flags ^= CPP_N_DEFAULT;
      flags |= CPP_N_MEDIUM;
    }

  /* Decode type based on width and properties. */
  if (flags & CPP_N_DFLOAT)
    if ((flags & CPP_N_WIDTH) == CPP_N_LARGE)
      type = dfloat128_type_node;
    else if ((flags & CPP_N_WIDTH) == CPP_N_SMALL)
      type = dfloat32_type_node;
    else
      type = dfloat64_type_node;
  else
    if ((flags & CPP_N_WIDTH) == CPP_N_LARGE)
      type = long_double_type_node;
    else if ((flags & CPP_N_WIDTH) == CPP_N_SMALL
	     || flag_single_precision_constant)
      type = float_type_node;
    else
      type = double_type_node;

  /* Copy the constant to a nul-terminated buffer.  If the constant
     has any suffixes, cut them off; REAL_VALUE_ATOF/ REAL_VALUE_HTOF
     can't handle them.  */
  copylen = token->val.str.len;
  if (flags & CPP_N_DFLOAT) 
    copylen -= 2;
  else 
    {
      if ((flags & CPP_N_WIDTH) != CPP_N_MEDIUM)
	/* Must be an F or L suffix.  */
	copylen--;
      if (flags & CPP_N_IMAGINARY)
	/* I or J suffix.  */
	copylen--;
    }

  copy = (char *) alloca (copylen + 1);
  memcpy (copy, token->val.str.text, copylen);
  copy[copylen] = '\0';

  real_from_string3 (&real, copy, TYPE_MODE (type));

  /* Both C and C++ require a diagnostic for a floating constant
     outside the range of representable values of its type.  Since we
     have __builtin_inf* to produce an infinity, it might now be
     appropriate for this to be a mandatory pedwarn rather than
     conditioned on -pedantic.  */
  if (REAL_VALUE_ISINF (real) && pedantic)
    pedwarn ("floating constant exceeds range of %qT", type);

  /* Create a node with determined type and value.  */
  value = build_real (type, real);
  if (flags & CPP_N_IMAGINARY)
    value = build_complex (NULL_TREE, convert (type, integer_zero_node), value);

  return value;
}