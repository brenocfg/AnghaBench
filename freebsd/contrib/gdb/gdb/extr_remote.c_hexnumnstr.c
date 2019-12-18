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
typedef  int ULONGEST ;

/* Variables and functions */

__attribute__((used)) static int
hexnumnstr (char *buf, ULONGEST num, int width)
{
  int i;

  buf[width] = '\0';

  for (i = width - 1; i >= 0; i--)
    {
      buf[i] = "0123456789abcdef"[(num & 0xf)];
      num >>= 4;
    }

  return width;
}