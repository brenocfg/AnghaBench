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

__attribute__((used)) static inline int
pop (int x)
{
  /* We assume that no more than 16 bits are used.  */
  x = ((x & ~0x5555) >> 1) + (x & 0x5555);
  x = ((x & ~0x3333) >> 2) + (x & 0x3333);
  x = ((x >> 4) + x) & 0x0f0f;
  x = ((x >> 8) + x) & 0xff;

  return x;
}