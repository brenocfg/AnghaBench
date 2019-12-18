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
struct ni_gpct_device {int /*<<< orphan*/  variant; } ;
struct ni_gpct {int /*<<< orphan*/  counter_index; struct ni_gpct_device* counter_dev; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int Gi_Arm_Bit ; 
 unsigned int Gi_Arm_Copy_Bit ; 
 unsigned int Gi_Disarm_Bit ; 
 unsigned int Gi_HW_Arm_Enable_Bit ; 
 unsigned int Gi_HW_Arm_Select_Mask (int /*<<< orphan*/ ) ; 
 unsigned int Gi_HW_Arm_Select_Shift ; 
 int /*<<< orphan*/  NITIO_Gi_Command_Reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NITIO_Gi_Counting_Mode_Reg (int /*<<< orphan*/ ) ; 
#define  NI_GPCT_ARM_IMMEDIATE 129 
#define  NI_GPCT_ARM_PAIRED_IMMEDIATE 128 
 unsigned int NI_GPCT_ARM_UNKNOWN ; 
 scalar_t__ ni_tio_counting_mode_registers_present (struct ni_gpct_device*) ; 
 int /*<<< orphan*/  ni_tio_set_bits (struct ni_gpct*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  ni_tio_set_bits_transient (struct ni_gpct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

int ni_tio_arm(struct ni_gpct *counter, int arm, unsigned start_trigger)
{
	struct ni_gpct_device *counter_dev = counter->counter_dev;

	unsigned command_transient_bits = 0;

	if (arm) {
		switch (start_trigger) {
		case NI_GPCT_ARM_IMMEDIATE:
			command_transient_bits |= Gi_Arm_Bit;
			break;
		case NI_GPCT_ARM_PAIRED_IMMEDIATE:
			command_transient_bits |= Gi_Arm_Bit | Gi_Arm_Copy_Bit;
			break;
		default:
			break;
		}
		if (ni_tio_counting_mode_registers_present(counter_dev)) {
			unsigned counting_mode_bits = 0;

			switch (start_trigger) {
			case NI_GPCT_ARM_IMMEDIATE:
			case NI_GPCT_ARM_PAIRED_IMMEDIATE:
				break;
			default:
				if (start_trigger & NI_GPCT_ARM_UNKNOWN) {
					/* pass-through the least significant bits so we can figure out what select later */
					unsigned hw_arm_select_bits =
					    (start_trigger <<
					     Gi_HW_Arm_Select_Shift) &
					    Gi_HW_Arm_Select_Mask
					    (counter_dev->variant);

					counting_mode_bits |=
					    Gi_HW_Arm_Enable_Bit |
					    hw_arm_select_bits;
				} else {
					return -EINVAL;
				}
				break;
			}
			ni_tio_set_bits(counter,
					NITIO_Gi_Counting_Mode_Reg
					(counter->counter_index),
					Gi_HW_Arm_Select_Mask
					(counter_dev->variant) |
					Gi_HW_Arm_Enable_Bit,
					counting_mode_bits);
		}
	} else {
		command_transient_bits |= Gi_Disarm_Bit;
	}
	ni_tio_set_bits_transient(counter,
				  NITIO_Gi_Command_Reg(counter->counter_index),
				  0, 0, command_transient_bits);
	return 0;
}