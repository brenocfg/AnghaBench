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
 int /*<<< orphan*/  PicoFrameStartMode4 () ; 
 int /*<<< orphan*/  PicoLineMode4 (int) ; 

void PicoFrameDrawOnlyMS(void)
{
  int lines_vis = 192;
  int y;

  PicoFrameStartMode4();

  for (y = 0; y < lines_vis; y++)
    PicoLineMode4(y);
}