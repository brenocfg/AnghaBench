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
 int FRAMES_PER_SECOND ; 
 scalar_t__ frame_rate ; 
 scalar_t__ frames_rendered ; 
 int tick_count ; 

void tick_handler(void)
{
  tick_count += 1;
  if(tick_count % FRAMES_PER_SECOND == 0)
  {
    frame_rate = frames_rendered;
    frames_rendered = 0;
  }
}