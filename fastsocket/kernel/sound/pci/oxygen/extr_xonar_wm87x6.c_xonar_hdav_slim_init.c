#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int anti_pop_delay; int /*<<< orphan*/  output_enable_bit; } ;
struct xonar_wm87x6 {int /*<<< orphan*/  hdmi; TYPE_1__ generic; } ;
struct oxygen {int /*<<< orphan*/  card; struct xonar_wm87x6* model_data; } ;

/* Variables and functions */
 int GPIO_SLIM_FIRMWARE_CLK ; 
 int GPIO_SLIM_FIRMWARE_DATA ; 
 int GPIO_SLIM_HDMI_DISABLE ; 
 int /*<<< orphan*/  GPIO_SLIM_OUTPUT_ENABLE ; 
 int /*<<< orphan*/  OXYGEN_GPIO_CONTROL ; 
 int /*<<< orphan*/  oxygen_set_bits16 (struct oxygen*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_component_add (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wm8776_init (struct oxygen*) ; 
 int /*<<< orphan*/  xonar_enable_output (struct oxygen*) ; 
 int /*<<< orphan*/  xonar_hdmi_init (struct oxygen*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xonar_hdav_slim_init(struct oxygen *chip)
{
	struct xonar_wm87x6 *data = chip->model_data;

	data->generic.anti_pop_delay = 300;
	data->generic.output_enable_bit = GPIO_SLIM_OUTPUT_ENABLE;

	wm8776_init(chip);

	oxygen_set_bits16(chip, OXYGEN_GPIO_CONTROL,
			  GPIO_SLIM_HDMI_DISABLE |
			  GPIO_SLIM_FIRMWARE_CLK |
			  GPIO_SLIM_FIRMWARE_DATA);

	xonar_hdmi_init(chip, &data->hdmi);
	xonar_enable_output(chip);

	snd_component_add(chip->card, "WM8776");
}