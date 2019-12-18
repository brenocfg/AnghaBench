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
typedef  scalar_t__* uarb ;

/* Variables and functions */

__attribute__((used)) static int
uarb_cmp(uarb a, int adigits, uarb b, int bdigits)
   /* Return -1/0/+1 according as a<b/a==b/a>b */
{
   if (adigits < bdigits)
      return -1;

   if (adigits > bdigits)
      return 1;

   while (adigits-- > 0)
      if (a[adigits] < b[adigits])
         return -1;

      else if (a[adigits] > b[adigits])
         return 1;

   return 0;
}