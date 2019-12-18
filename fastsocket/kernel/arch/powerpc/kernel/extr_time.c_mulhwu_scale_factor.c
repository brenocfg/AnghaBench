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
 unsigned int mulhwu (unsigned int,unsigned int) ; 

unsigned mulhwu_scale_factor(unsigned inscale, unsigned outscale)
{
        unsigned mlt=0, tmp, err;
        /* No concern for performance, it's done once: use a stupid
         * but safe and compact method to find the multiplier.
         */
  
        for (tmp = 1U<<31; tmp != 0; tmp >>= 1) {
                if (mulhwu(inscale, mlt|tmp) < outscale)
			mlt |= tmp;
        }
  
        /* We might still be off by 1 for the best approximation.
         * A side effect of this is that if outscale is too large
         * the returned value will be zero.
         * Many corner cases have been checked and seem to work,
         * some might have been forgotten in the test however.
         */
  
        err = inscale * (mlt+1);
        if (err <= inscale/2)
		mlt++;
        return mlt;
}