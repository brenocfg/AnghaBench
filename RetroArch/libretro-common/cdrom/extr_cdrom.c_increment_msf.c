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

void increment_msf(unsigned char *min, unsigned char *sec, unsigned char *frame)
{
   if (!min || !sec || !frame)
      return;

   *min = (*frame == 74) ? (*sec < 59 ? *min : *min + 1) : *min;
   *sec = (*frame == 74) ? (*sec < 59 ? (*sec + 1) : 0) : *sec;
   *frame = (*frame < 74) ? (*frame + 1) : 0;
}