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
typedef  int srep_t ;
typedef  int rep_t ;
typedef  int /*<<< orphan*/  fp_t ;
typedef  enum LE_RESULT { ____Placeholder_LE_RESULT } LE_RESULT ;

/* Variables and functions */
 int LE_EQUAL ; 
 int LE_GREATER ; 
 int LE_LESS ; 
 int LE_UNORDERED ; 
 int const absMask ; 
 int const infRep ; 
 int toRep (int /*<<< orphan*/ ) ; 

enum LE_RESULT __lesf2(fp_t a, fp_t b) {

  const srep_t aInt = toRep(a);
  const srep_t bInt = toRep(b);
  const rep_t aAbs = aInt & absMask;
  const rep_t bAbs = bInt & absMask;

  // If either a or b is NaN, they are unordered.
  if (aAbs > infRep || bAbs > infRep)
    return LE_UNORDERED;

  // If a and b are both zeros, they are equal.
  if ((aAbs | bAbs) == 0)
    return LE_EQUAL;

  // If at least one of a and b is positive, we get the same result comparing
  // a and b as signed integers as we would with a fp_ting-point compare.
  if ((aInt & bInt) >= 0) {
    if (aInt < bInt)
      return LE_LESS;
    else if (aInt == bInt)
      return LE_EQUAL;
    else
      return LE_GREATER;
  }

  // Otherwise, both are negative, so we need to flip the sense of the
  // comparison to get the correct result.  (This assumes a twos- or ones-
  // complement integer representation; if integers are represented in a
  // sign-magnitude representation, then this flip is incorrect).
  else {
    if (aInt > bInt)
      return LE_LESS;
    else if (aInt == bInt)
      return LE_EQUAL;
    else
      return LE_GREATER;
  }
}