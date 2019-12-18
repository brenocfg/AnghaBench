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
 int /*<<< orphan*/  PicoFrameHints () ; 
 int /*<<< orphan*/  PicoFrameStart () ; 
 int /*<<< orphan*/  pcd_prepare_frame () ; 

void PicoFrameMCD(void)
{
  PicoFrameStart();

  pcd_prepare_frame();
  PicoFrameHints();
}