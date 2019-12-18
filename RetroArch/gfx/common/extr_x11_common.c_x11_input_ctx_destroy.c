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
 int /*<<< orphan*/  g_x11_xic ; 
 int /*<<< orphan*/  g_x11_xim ; 
 int /*<<< orphan*/  x11_destroy_input_context (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void x11_input_ctx_destroy(void)
{
   x11_destroy_input_context(&g_x11_xim, &g_x11_xic);
}