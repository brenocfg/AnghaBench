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
typedef  int /*<<< orphan*/  SwsContext ;

/* Variables and functions */
 int av_get_cpu_flags () ; 
 int /*<<< orphan*/  get_unscaled_swscale_neon (int /*<<< orphan*/ *) ; 
 scalar_t__ have_neon (int) ; 

void ff_get_unscaled_swscale_aarch64(SwsContext *c)
{
    int cpu_flags = av_get_cpu_flags();
    if (have_neon(cpu_flags))
        get_unscaled_swscale_neon(c);
}