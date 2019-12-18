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

/* Variables and functions */
 scalar_t__ TYPE_MAIN_VARIANT (scalar_t__) ; 
 scalar_t__ c_common_signed_or_unsigned_type (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ char_type_node ; 
 scalar_t__ intDI_type_node ; 
 scalar_t__ intHI_type_node ; 
 scalar_t__ intQI_type_node ; 
 scalar_t__ intSI_type_node ; 
 scalar_t__ intTI_type_node ; 
 scalar_t__ integer_type_node ; 
 scalar_t__ long_integer_type_node ; 
 scalar_t__ long_long_integer_type_node ; 
 scalar_t__ long_long_unsigned_type_node ; 
 scalar_t__ long_unsigned_type_node ; 
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
 scalar_t__ widest_integer_literal_type_node ; 
 scalar_t__ widest_unsigned_literal_type_node ; 

tree
c_common_signed_type (tree type)
{
  tree type1 = TYPE_MAIN_VARIANT (type);
  if (type1 == unsigned_char_type_node || type1 == char_type_node)
    return signed_char_type_node;
  if (type1 == unsigned_type_node)
    return integer_type_node;
  if (type1 == short_unsigned_type_node)
    return short_integer_type_node;
  if (type1 == long_unsigned_type_node)
    return long_integer_type_node;
  if (type1 == long_long_unsigned_type_node)
    return long_long_integer_type_node;
  if (type1 == widest_unsigned_literal_type_node)
    return widest_integer_literal_type_node;
#if HOST_BITS_PER_WIDE_INT >= 64
  if (type1 == unsigned_intTI_type_node)
    return intTI_type_node;
#endif
  if (type1 == unsigned_intDI_type_node)
    return intDI_type_node;
  if (type1 == unsigned_intSI_type_node)
    return intSI_type_node;
  if (type1 == unsigned_intHI_type_node)
    return intHI_type_node;
  if (type1 == unsigned_intQI_type_node)
    return intQI_type_node;

  return c_common_signed_or_unsigned_type (0, type);
}