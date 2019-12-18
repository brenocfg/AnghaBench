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
typedef  int HOST_WIDE_INT ;

/* Variables and functions */

int
size_of_sleb128 (HOST_WIDE_INT value)
{
  int size = 0, byte;

  do
    {
      byte = (value & 0x7f);
      value >>= 7;
      size += 1;
    }
  while (!((value == 0 && (byte & 0x40) == 0)
	   || (value == -1 && (byte & 0x40) != 0)));

  return size;
}