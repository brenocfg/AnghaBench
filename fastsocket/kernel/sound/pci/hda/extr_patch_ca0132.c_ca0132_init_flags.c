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
 int /*<<< orphan*/  CONTROL_FLAG_ADC_C_HIGH_PASS ; 
 int /*<<< orphan*/  CONTROL_FLAG_IDLE_ENABLE ; 
 int /*<<< orphan*/  CONTROL_FLAG_PORT_A_10KOHM_LOAD ; 
 int /*<<< orphan*/  CONTROL_FLAG_PORT_A_COMMON_MODE ; 
 int /*<<< orphan*/  CONTROL_FLAG_PORT_D_10KOHM_LOAD ; 
 int /*<<< orphan*/  CONTROL_FLAG_PORT_D_COMMON_MODE ; 
 int /*<<< orphan*/  chipio_set_control_flag (struct hda_codec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ca0132_init_flags(struct hda_codec *codec)
{
	chipio_set_control_flag(codec, CONTROL_FLAG_IDLE_ENABLE, 0);
	chipio_set_control_flag(codec, CONTROL_FLAG_PORT_A_COMMON_MODE, 0);
	chipio_set_control_flag(codec, CONTROL_FLAG_PORT_D_COMMON_MODE, 0);
	chipio_set_control_flag(codec, CONTROL_FLAG_PORT_A_10KOHM_LOAD, 0);
	chipio_set_control_flag(codec, CONTROL_FLAG_PORT_D_10KOHM_LOAD, 0);
	chipio_set_control_flag(codec, CONTROL_FLAG_ADC_C_HIGH_PASS, 1);
}