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
typedef  int rep_t ;
typedef  int /*<<< orphan*/  fp_t ;
typedef  int const fixuint_t ;

/* Variables and functions */
 int CHAR_BIT ; 
 int const absMask ; 
 int const exponentBias ; 
 int const implicitBit ; 
 int const signBit ; 
 int const significandBits ; 
 int const significandMask ; 
 int toRep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline fixuint_t __fixuint(fp_t a) {
  // Break a into sign, exponent, significand parts.
  const rep_t aRep = toRep(a);
  const rep_t aAbs = aRep & absMask;
  const int sign = aRep & signBit ? -1 : 1;
  const int exponent = (aAbs >> significandBits) - exponentBias;
  const rep_t significand = (aAbs & significandMask) | implicitBit;

  // If either the value or the exponent is negative, the result is zero.
  if (sign == -1 || exponent < 0)
    return 0;

  // If the value is too large for the integer type, saturate.
  if ((unsigned)exponent >= sizeof(fixuint_t) * CHAR_BIT)
    return ~(fixuint_t)0;

  // If 0 <= exponent < significandBits, right shift to get the result.
  // Otherwise, shift left.
  if (exponent < significandBits)
    return significand >> (significandBits - exponent);
  else
    return (fixuint_t)significand << (exponent - significandBits);
}