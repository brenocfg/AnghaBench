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

__attribute__((used)) static unsigned bi_reverse(unsigned codes, int len)
   {
      register unsigned res = 0;
      do {
         res |= codes & 1;
         codes >>= 1, res <<= 1;
      } while (--len > 0);
      return res >> 1;
   }