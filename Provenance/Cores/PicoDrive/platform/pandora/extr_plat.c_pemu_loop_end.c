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

/* Variables and functions */
 int /*<<< orphan*/  g_layer_h ; 
 int /*<<< orphan*/  g_layer_w ; 
 int /*<<< orphan*/  g_layer_x ; 
 int /*<<< orphan*/  g_layer_y ; 
 int /*<<< orphan*/  pemu_forced_frame (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pnd_setup_layer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void pemu_loop_end(void)
{
	/* do one more frame for menu bg */
	pemu_forced_frame(0, 1);

	pnd_setup_layer(0, g_layer_x, g_layer_y, g_layer_w, g_layer_h);
}