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

__attribute__((used)) static unsigned bitswap(unsigned x, unsigned size_log2)
{
   unsigned i;
   unsigned ret = 0;
   for (i = 0; i < size_log2; i++)
      ret |= ((x >> i) & 1) << (size_log2 - i - 1);
   return ret;
}