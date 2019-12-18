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
 unsigned char pad_index ; 

void wayplay_2_write(unsigned char data, unsigned char mask)
{
  if ((mask & 0x70) == 0x70)
  {
    pad_index = (data & 0x70) >> 4;
  }
}