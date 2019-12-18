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
struct hda_codec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL_PARAM_PORTA_160OHM_GAIN ; 
 int /*<<< orphan*/  CONTROL_PARAM_PORTD_160OHM_GAIN ; 
 int /*<<< orphan*/  chipio_set_control_param (struct hda_codec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ca0132_init_params(struct hda_codec *codec)
{
	chipio_set_control_param(codec, CONTROL_PARAM_PORTA_160OHM_GAIN, 6);
	chipio_set_control_param(codec, CONTROL_PARAM_PORTD_160OHM_GAIN, 6);
}