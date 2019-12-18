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

__attribute__((used)) static void empty(volatile char *against)
{
  /* We know that there's a 16 k cache with 64 byte lines giving
     a total of 256 lines.  Read randomly from 256*5 places should
     flush everything */
  int offset = (1024 - 256)*1024;

  for (int i = offset; i < offset + 16*1024*3; i += 64)
    {
      against[i];
    }
}