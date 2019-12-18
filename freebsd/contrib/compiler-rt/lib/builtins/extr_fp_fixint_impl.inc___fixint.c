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
typedef  int fixuint_t ;
typedef  int fixint_t ;

/* Variables and functions */
 int CHAR_BIT ; 
 int const absMask ; 
 int const exponentBias ; 
 int const implicitBit ; 
 int const signBit ; 
 int const significandBits ; 
 int const significandMask ; 
 int toRep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline fixint_t __fixint(fp_t a) {
  const fixint_t fixint_max = (fixint_t)((~(fixuint_t)0) / 2);
  const fixint_t fixint_min = -fixint_max - 1;
  // Break a into sign, exponent, significand parts.
  const rep_t aRep = toRep(a);
  const rep_t aAbs = aRep & absMask;
  const fixint_t sign = aRep & signBit ? -1 : 1;
  const int exponent = (aAbs >> significandBits) - exponentBias;
  const rep_t significand = (aAbs & significandMask) | implicitBit;

  // If exponent is negative, the result is zero.
  if (exponent < 0)
    return 0;

  // If the value is too large for the integer type, saturate.
  if ((unsigned)exponent >= sizeof(fixint_t) * CHAR_BIT)
    return sign == 1 ? fixint_max : fixint_min;

  // If 0 <= exponent < significandBits, right shift to get the result.
  // Otherwise, shift left.
  if (exponent < significandBits)
    return sign * (significand >> (significandBits - exponent));
  else
    return sign * ((fixint_t)significand << (exponent - significandBits));
}