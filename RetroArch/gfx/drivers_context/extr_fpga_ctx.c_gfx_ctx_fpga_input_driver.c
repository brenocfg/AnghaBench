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
typedef  int /*<<< orphan*/  settings_t ;
typedef  int /*<<< orphan*/  input_driver_t ;

/* Variables and functions */
 int /*<<< orphan*/ * config_get_ptr () ; 

__attribute__((used)) static void gfx_ctx_fpga_input_driver(void *data,
      const char *joypad_name,
      const input_driver_t **input, void **input_data)
{
   (void)data;
   settings_t *settings = config_get_ptr();
}