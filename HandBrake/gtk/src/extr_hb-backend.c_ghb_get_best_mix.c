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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ gint ;

/* Variables and functions */
 scalar_t__ HB_AMIXDOWN_NONE ; 
 scalar_t__ HB_INVALID_AMIXDOWN ; 
 scalar_t__ hb_mixdown_get_best (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

gint
ghb_get_best_mix(uint64_t layout, gint acodec, gint mix)
{
    if (mix == HB_AMIXDOWN_NONE)
        mix = HB_INVALID_AMIXDOWN;

    return hb_mixdown_get_best(acodec, layout, mix);
}