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
typedef  int /*<<< orphan*/  SwsFunc ;
typedef  int /*<<< orphan*/  SwsContext ;

/* Variables and functions */
 scalar_t__ ARCH_AARCH64 ; 
 scalar_t__ ARCH_ARM ; 
 scalar_t__ ARCH_PPC ; 
 scalar_t__ ARCH_X86 ; 
 int /*<<< orphan*/  ff_sws_init_swscale_aarch64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_sws_init_swscale_arm (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_sws_init_swscale_ppc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_sws_init_swscale_x86 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sws_init_swscale (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swscale ; 

SwsFunc ff_getSwsFunc(SwsContext *c)
{
    sws_init_swscale(c);

    if (ARCH_PPC)
        ff_sws_init_swscale_ppc(c);
    if (ARCH_X86)
        ff_sws_init_swscale_x86(c);
    if (ARCH_AARCH64)
        ff_sws_init_swscale_aarch64(c);
    if (ARCH_ARM)
        ff_sws_init_swscale_arm(c);

    return swscale;
}