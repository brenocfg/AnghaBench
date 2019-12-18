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
typedef  int valueT ;

/* Variables and functions */
 int LITTLENUM_MASK ; 
 int LITTLENUM_NUMBER_OF_BITS ; 
 int* generic_bignum ; 

__attribute__((used)) static valueT
generic_bignum_to_int32 (void)
{
  valueT number =
	   ((generic_bignum[1] & LITTLENUM_MASK) << LITTLENUM_NUMBER_OF_BITS)
	   | (generic_bignum[0] & LITTLENUM_MASK);
  number &= 0xffffffff;
  return number;
}