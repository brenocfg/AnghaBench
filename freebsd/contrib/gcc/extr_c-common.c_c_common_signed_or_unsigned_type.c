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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 int /*<<< orphan*/  INTEGRAL_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_PRECISION (int /*<<< orphan*/ ) ; 
 int TYPE_UNSIGNED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_nonstandard_integer_type (int /*<<< orphan*/ ,int) ; 
 scalar_t__ c_dialect_cxx () ; 
 int /*<<< orphan*/  intDI_type_node ; 
 int /*<<< orphan*/  intHI_type_node ; 
 int /*<<< orphan*/  intQI_type_node ; 
 int /*<<< orphan*/  intSI_type_node ; 
 int /*<<< orphan*/  intTI_type_node ; 
 int /*<<< orphan*/  integer_type_node ; 
 int /*<<< orphan*/  long_integer_type_node ; 
 int /*<<< orphan*/  long_long_integer_type_node ; 
 int /*<<< orphan*/  long_long_unsigned_type_node ; 
 int /*<<< orphan*/  long_unsigned_type_node ; 
 int /*<<< orphan*/  short_integer_type_node ; 
 int /*<<< orphan*/  short_unsigned_type_node ; 
 int /*<<< orphan*/  signed_char_type_node ; 
 int /*<<< orphan*/  unsigned_char_type_node ; 
 int /*<<< orphan*/  unsigned_intDI_type_node ; 
 int /*<<< orphan*/  unsigned_intHI_type_node ; 
 int /*<<< orphan*/  unsigned_intQI_type_node ; 
 int /*<<< orphan*/  unsigned_intSI_type_node ; 
 int /*<<< orphan*/  unsigned_intTI_type_node ; 
 int /*<<< orphan*/  unsigned_type_node ; 
 int /*<<< orphan*/  widest_integer_literal_type_node ; 
 int /*<<< orphan*/  widest_unsigned_literal_type_node ; 

tree
c_common_signed_or_unsigned_type (int unsignedp, tree type)
{
  if (!INTEGRAL_TYPE_P (type)
      || TYPE_UNSIGNED (type) == unsignedp)
    return type;

  /* For ENUMERAL_TYPEs in C++, must check the mode of the types, not
     the precision; they have precision set to match their range, but
     may use a wider mode to match an ABI.  If we change modes, we may
     wind up with bad conversions.  For INTEGER_TYPEs in C, must check
     the precision as well, so as to yield correct results for
     bit-field types.  C++ does not have these separate bit-field
     types, and producing a signed or unsigned variant of an
     ENUMERAL_TYPE may cause other problems as well.  */

#define TYPE_OK(node)							    \
  (TYPE_MODE (type) == TYPE_MODE (node)					    \
   && (c_dialect_cxx () || TYPE_PRECISION (type) == TYPE_PRECISION (node)))
  if (TYPE_OK (signed_char_type_node))
    return unsignedp ? unsigned_char_type_node : signed_char_type_node;
  if (TYPE_OK (integer_type_node))
    return unsignedp ? unsigned_type_node : integer_type_node;
  if (TYPE_OK (short_integer_type_node))
    return unsignedp ? short_unsigned_type_node : short_integer_type_node;
  if (TYPE_OK (long_integer_type_node))
    return unsignedp ? long_unsigned_type_node : long_integer_type_node;
  if (TYPE_OK (long_long_integer_type_node))
    return (unsignedp ? long_long_unsigned_type_node
	    : long_long_integer_type_node);
  if (TYPE_OK (widest_integer_literal_type_node))
    return (unsignedp ? widest_unsigned_literal_type_node
	    : widest_integer_literal_type_node);

#if HOST_BITS_PER_WIDE_INT >= 64
  if (TYPE_OK (intTI_type_node))
    return unsignedp ? unsigned_intTI_type_node : intTI_type_node;
#endif
  if (TYPE_OK (intDI_type_node))
    return unsignedp ? unsigned_intDI_type_node : intDI_type_node;
  if (TYPE_OK (intSI_type_node))
    return unsignedp ? unsigned_intSI_type_node : intSI_type_node;
  if (TYPE_OK (intHI_type_node))
    return unsignedp ? unsigned_intHI_type_node : intHI_type_node;
  if (TYPE_OK (intQI_type_node))
    return unsignedp ? unsigned_intQI_type_node : intQI_type_node;
#undef TYPE_OK

  if (c_dialect_cxx ())
    return type;
  else
    return build_nonstandard_integer_type (TYPE_PRECISION (type), unsignedp);
}