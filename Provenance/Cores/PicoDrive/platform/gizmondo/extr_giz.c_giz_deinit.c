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
 int /*<<< orphan*/  Framework2D_Close () ; 
 int /*<<< orphan*/  Framework_Close () ; 
 int /*<<< orphan*/  directfb_fini () ; 
 int /*<<< orphan*/  giz_log_close () ; 

void giz_deinit(void)
{
	Framework2D_Close();
	Framework_Close();
#if 0
	directfb_fini();
#endif

	giz_log_close();
}