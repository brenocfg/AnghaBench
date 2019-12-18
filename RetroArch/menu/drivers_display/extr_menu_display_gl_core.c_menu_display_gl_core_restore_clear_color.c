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
 int /*<<< orphan*/  glClearColor (float,float,float,float) ; 

__attribute__((used)) static void menu_display_gl_core_restore_clear_color(void)
{
   glClearColor(0.0f, 0.0f, 0.0f, 0.00f);
}