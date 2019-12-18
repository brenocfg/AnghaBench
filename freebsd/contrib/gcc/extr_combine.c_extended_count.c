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
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int GET_MODE_BITSIZE (int) ; 
 int HOST_BITS_PER_WIDE_INT ; 
 int floor_log2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nonzero_bits (int /*<<< orphan*/ ,int) ; 
 scalar_t__ nonzero_sign_valid ; 
 int num_sign_bit_copies (int /*<<< orphan*/ ,int) ; 

unsigned int
extended_count (rtx x, enum machine_mode mode, int unsignedp)
{
  if (nonzero_sign_valid == 0)
    return 0;

  return (unsignedp
	  ? (GET_MODE_BITSIZE (mode) <= HOST_BITS_PER_WIDE_INT
	     ? (unsigned int) (GET_MODE_BITSIZE (mode) - 1
			       - floor_log2 (nonzero_bits (x, mode)))
	     : 0)
	  : num_sign_bit_copies (x, mode) - 1);
}