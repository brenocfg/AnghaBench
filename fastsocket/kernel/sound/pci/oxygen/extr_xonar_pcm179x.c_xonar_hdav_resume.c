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
struct xonar_hdav {int /*<<< orphan*/  hdmi; } ;
struct oxygen {struct xonar_hdav* model_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  pcm1796_registers_init (struct oxygen*) ; 
 int /*<<< orphan*/  xonar_enable_output (struct oxygen*) ; 
 int /*<<< orphan*/  xonar_hdmi_resume (struct oxygen*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xonar_hdav_resume(struct oxygen *chip)
{
	struct xonar_hdav *data = chip->model_data;

	pcm1796_registers_init(chip);
	xonar_hdmi_resume(chip, &data->hdmi);
	xonar_enable_output(chip);
}