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
typedef  int /*<<< orphan*/ * uarb ;

/* Variables and functions */

__attribute__((used)) static int
uarb_copy(uarb to, uarb from, int idigits)
   /* Copy a uarb, may reduce the digit count */
{
   int d, odigits;

   for (d=odigits=0; d<idigits; ++d)
      if ((to[d] = from[d]) != 0)
         odigits = d+1;

   return odigits;
}