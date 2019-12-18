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
typedef  scalar_t__ tree ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ COMPLEX_MODE_P (int) ; 
 int DImode ; 
 int GET_MODE_INNER (int) ; 
 int /*<<< orphan*/  GET_MODE_PRECISION (int) ; 
 int HImode ; 
 scalar_t__ NULL_TREE ; 
 int QImode ; 
 int SImode ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 int TYPE_MODE (scalar_t__) ; 
 scalar_t__ VECTOR_MODE_P (int) ; 
 scalar_t__ build_complex_type (scalar_t__) ; 
 scalar_t__ build_pointer_type (scalar_t__) ; 
 scalar_t__ build_vector_type_for_mode (scalar_t__,int) ; 
 scalar_t__ char_type_node ; 
 scalar_t__ complex_double_type_node ; 
 scalar_t__ complex_float_type_node ; 
 scalar_t__ complex_integer_type_node ; 
 scalar_t__ complex_long_double_type_node ; 
 scalar_t__ dfloat128_type_node ; 
 scalar_t__ dfloat32_type_node ; 
 scalar_t__ dfloat64_type_node ; 
 scalar_t__ double_type_node ; 
 scalar_t__ float_type_node ; 
 scalar_t__ intDI_type_node ; 
 scalar_t__ intHI_type_node ; 
 scalar_t__ intQI_type_node ; 
 scalar_t__ intSI_type_node ; 
 scalar_t__ intTI_type_node ; 
 scalar_t__ integer_type_node ; 
 scalar_t__ long_double_type_node ; 
 scalar_t__ long_integer_type_node ; 
 scalar_t__ long_long_integer_type_node ; 
 scalar_t__ long_long_unsigned_type_node ; 
 scalar_t__ long_unsigned_type_node ; 
 scalar_t__ make_signed_type (int /*<<< orphan*/ ) ; 
 scalar_t__ make_unsigned_type (int /*<<< orphan*/ ) ; 
 scalar_t__ registered_builtin_types ; 
 scalar_t__ short_integer_type_node ; 
 scalar_t__ short_unsigned_type_node ; 
 scalar_t__ signed_char_type_node ; 
 scalar_t__ unsigned_char_type_node ; 
 scalar_t__ unsigned_intDI_type_node ; 
 scalar_t__ unsigned_intHI_type_node ; 
 scalar_t__ unsigned_intQI_type_node ; 
 scalar_t__ unsigned_intSI_type_node ; 
 scalar_t__ unsigned_intTI_type_node ; 
 scalar_t__ unsigned_type_node ; 
 scalar_t__ void_type_node ; 
 scalar_t__ widest_integer_literal_type_node ; 
 scalar_t__ widest_unsigned_literal_type_node ; 

tree
c_common_type_for_mode (enum machine_mode mode, int unsignedp)
{
  tree t;

  if (mode == TYPE_MODE (integer_type_node))
    return unsignedp ? unsigned_type_node : integer_type_node;

  if (mode == TYPE_MODE (signed_char_type_node))
    return unsignedp ? unsigned_char_type_node : signed_char_type_node;

  if (mode == TYPE_MODE (short_integer_type_node))
    return unsignedp ? short_unsigned_type_node : short_integer_type_node;

  if (mode == TYPE_MODE (long_integer_type_node))
    return unsignedp ? long_unsigned_type_node : long_integer_type_node;

  if (mode == TYPE_MODE (long_long_integer_type_node))
    return unsignedp ? long_long_unsigned_type_node : long_long_integer_type_node;

  if (mode == TYPE_MODE (widest_integer_literal_type_node))
    return unsignedp ? widest_unsigned_literal_type_node
		     : widest_integer_literal_type_node;

  if (mode == QImode)
    return unsignedp ? unsigned_intQI_type_node : intQI_type_node;

  if (mode == HImode)
    return unsignedp ? unsigned_intHI_type_node : intHI_type_node;

  if (mode == SImode)
    return unsignedp ? unsigned_intSI_type_node : intSI_type_node;

  if (mode == DImode)
    return unsignedp ? unsigned_intDI_type_node : intDI_type_node;

#if HOST_BITS_PER_WIDE_INT >= 64
  if (mode == TYPE_MODE (intTI_type_node))
    return unsignedp ? unsigned_intTI_type_node : intTI_type_node;
#endif

  if (mode == TYPE_MODE (float_type_node))
    return float_type_node;

  if (mode == TYPE_MODE (double_type_node))
    return double_type_node;

  if (mode == TYPE_MODE (long_double_type_node))
    return long_double_type_node;

  if (mode == TYPE_MODE (void_type_node))
    return void_type_node;

  if (mode == TYPE_MODE (build_pointer_type (char_type_node)))
    return (unsignedp
	    ? make_unsigned_type (GET_MODE_PRECISION (mode))
	    : make_signed_type (GET_MODE_PRECISION (mode)));

  if (mode == TYPE_MODE (build_pointer_type (integer_type_node)))
    return (unsignedp
	    ? make_unsigned_type (GET_MODE_PRECISION (mode))
	    : make_signed_type (GET_MODE_PRECISION (mode)));

  if (COMPLEX_MODE_P (mode))
    {
      enum machine_mode inner_mode;
      tree inner_type;

      if (mode == TYPE_MODE (complex_float_type_node))
	return complex_float_type_node;
      if (mode == TYPE_MODE (complex_double_type_node))
	return complex_double_type_node;
      if (mode == TYPE_MODE (complex_long_double_type_node))
	return complex_long_double_type_node;

      if (mode == TYPE_MODE (complex_integer_type_node) && !unsignedp)
	return complex_integer_type_node;

      inner_mode = GET_MODE_INNER (mode);
      inner_type = c_common_type_for_mode (inner_mode, unsignedp);
      if (inner_type != NULL_TREE)
	return build_complex_type (inner_type);
    }
  else if (VECTOR_MODE_P (mode))
    {
      enum machine_mode inner_mode = GET_MODE_INNER (mode);
      tree inner_type = c_common_type_for_mode (inner_mode, unsignedp);
      if (inner_type != NULL_TREE)
	return build_vector_type_for_mode (inner_type, mode);
    }

  if (mode == TYPE_MODE (dfloat32_type_node))
    return dfloat32_type_node;
  if (mode == TYPE_MODE (dfloat64_type_node))
    return dfloat64_type_node;
  if (mode == TYPE_MODE (dfloat128_type_node))
    return dfloat128_type_node;

  for (t = registered_builtin_types; t; t = TREE_CHAIN (t))
    if (TYPE_MODE (TREE_VALUE (t)) == mode)
      return TREE_VALUE (t);

  return 0;
}