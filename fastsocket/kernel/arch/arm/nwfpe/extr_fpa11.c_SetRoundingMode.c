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
typedef  int /*<<< orphan*/  int8 ;

/* Variables and functions */
 unsigned int const MASK_ROUNDING_MODE ; 
#define  ROUND_TO_MINUS_INFINITY 131 
#define  ROUND_TO_NEAREST 130 
#define  ROUND_TO_PLUS_INFINITY 129 
#define  ROUND_TO_ZERO 128 
 int /*<<< orphan*/  float_round_down ; 
 int /*<<< orphan*/  float_round_nearest_even ; 
 int /*<<< orphan*/  float_round_to_zero ; 
 int /*<<< orphan*/  float_round_up ; 

int8 SetRoundingMode(const unsigned int opcode)
{
	switch (opcode & MASK_ROUNDING_MODE) {
	default:
	case ROUND_TO_NEAREST:
		return float_round_nearest_even;

	case ROUND_TO_PLUS_INFINITY:
		return float_round_up;

	case ROUND_TO_MINUS_INFINITY:
		return float_round_down;

	case ROUND_TO_ZERO:
		return float_round_to_zero;
	}
}