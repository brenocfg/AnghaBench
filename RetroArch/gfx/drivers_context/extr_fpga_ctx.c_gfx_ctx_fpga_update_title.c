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
typedef  int /*<<< orphan*/  title ;

/* Variables and functions */
 int /*<<< orphan*/  video_driver_get_window_title (char*,int) ; 

__attribute__((used)) static void gfx_ctx_fpga_update_title(void *data, void *data2)
{
   char title[128];

   title[0] = '\0';

   video_driver_get_window_title(title, sizeof(title));
}