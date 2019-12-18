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
struct eq_gain {scalar_t__ freq; } ;

/* Variables and functions */

__attribute__((used)) static int gains_cmp(const void *a_, const void *b_)
{
   const struct eq_gain *a = (const struct eq_gain*)a_;
   const struct eq_gain *b = (const struct eq_gain*)b_;
   if (a->freq < b->freq)
      return -1;
   if (a->freq > b->freq)
      return 1;
   return 0;
}