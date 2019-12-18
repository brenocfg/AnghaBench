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
 int /*<<< orphan*/ * image_buffer ; 
 scalar_t__ image_height ; 
 scalar_t__ image_width ; 

__attribute__((used)) static void imageviewer_reset(void)
{
   image_buffer = NULL;
   image_width  = 0;
   image_height = 0;
}