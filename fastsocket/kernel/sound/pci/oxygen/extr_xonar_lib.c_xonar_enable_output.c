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
struct xonar_generic {int /*<<< orphan*/  output_enable_bit; int /*<<< orphan*/  anti_pop_delay; } ;
struct oxygen {struct xonar_generic* model_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  OXYGEN_GPIO_CONTROL ; 
 int /*<<< orphan*/  OXYGEN_GPIO_DATA ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oxygen_set_bits16 (struct oxygen*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void xonar_enable_output(struct oxygen *chip)
{
	struct xonar_generic *data = chip->model_data;

	oxygen_set_bits16(chip, OXYGEN_GPIO_CONTROL, data->output_enable_bit);
	msleep(data->anti_pop_delay);
	oxygen_set_bits16(chip, OXYGEN_GPIO_DATA, data->output_enable_bit);
}