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
 int /*<<< orphan*/  font_driver_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * video_font_driver ; 

void font_driver_free_osd(void)
{
   if (video_font_driver)
      font_driver_free(video_font_driver);

   video_font_driver = NULL;
}