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

void cdrom_lba_to_msf(unsigned lba, unsigned char *min, unsigned char *sec, unsigned char *frame)
{
   if (!min || !sec || !frame)
      return;

   *frame = lba % 75;
   lba /= 75;
   *sec = lba % 60;
   lba /= 60;
   *min = lba;
}