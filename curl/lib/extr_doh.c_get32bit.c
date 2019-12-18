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

__attribute__((used)) static unsigned int get32bit(unsigned char *doh, int index)
{
   /* make clang and gcc optimize this to bswap by incrementing
      the pointer first. */
   doh += index;

   /* avoid undefined behaviour by casting to unsigned before shifting
      24 bits, possibly into the sign bit. codegen is same, but
      ub sanitizer won't be upset */
  return ( (unsigned)doh[0] << 24) | (doh[1] << 16) |(doh[2] << 8) | doh[3];
}