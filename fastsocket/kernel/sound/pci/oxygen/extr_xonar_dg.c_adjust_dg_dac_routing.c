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
struct oxygen {int dummy; } ;

/* Variables and functions */
 unsigned int OXYGEN_PLAY_DAC0_SOURCE_MASK ; 
 int /*<<< orphan*/  OXYGEN_PLAY_DAC0_SOURCE_SHIFT ; 
 int /*<<< orphan*/  OXYGEN_PLAY_DAC1_SOURCE_MASK ; 
 int /*<<< orphan*/  OXYGEN_PLAY_DAC1_SOURCE_SHIFT ; 
 int /*<<< orphan*/  OXYGEN_PLAY_DAC2_SOURCE_MASK ; 
 int /*<<< orphan*/  OXYGEN_PLAY_DAC2_SOURCE_SHIFT ; 
 int /*<<< orphan*/  OXYGEN_PLAY_DAC3_SOURCE_MASK ; 
 int /*<<< orphan*/  OXYGEN_PLAY_DAC3_SOURCE_SHIFT ; 
 unsigned int shift_bits (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int adjust_dg_dac_routing(struct oxygen *chip,
					  unsigned int play_routing)
{
	return (play_routing & OXYGEN_PLAY_DAC0_SOURCE_MASK) |
	       shift_bits(play_routing,
			  OXYGEN_PLAY_DAC2_SOURCE_SHIFT,
			  OXYGEN_PLAY_DAC1_SOURCE_SHIFT,
			  OXYGEN_PLAY_DAC1_SOURCE_MASK) |
	       shift_bits(play_routing,
			  OXYGEN_PLAY_DAC1_SOURCE_SHIFT,
			  OXYGEN_PLAY_DAC2_SOURCE_SHIFT,
			  OXYGEN_PLAY_DAC2_SOURCE_MASK) |
	       shift_bits(play_routing,
			  OXYGEN_PLAY_DAC0_SOURCE_SHIFT,
			  OXYGEN_PLAY_DAC3_SOURCE_SHIFT,
			  OXYGEN_PLAY_DAC3_SOURCE_MASK);
}