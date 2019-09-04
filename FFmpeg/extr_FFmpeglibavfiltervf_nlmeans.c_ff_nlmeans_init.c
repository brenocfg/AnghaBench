#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  compute_safe_ssd_integral_image; } ;
typedef  TYPE_1__ NLMeansDSPContext ;

/* Variables and functions */
 scalar_t__ ARCH_AARCH64 ; 
 int /*<<< orphan*/  compute_safe_ssd_integral_image_c ; 
 int /*<<< orphan*/  ff_nlmeans_init_aarch64 (TYPE_1__*) ; 

void ff_nlmeans_init(NLMeansDSPContext *dsp)
{
    dsp->compute_safe_ssd_integral_image = compute_safe_ssd_integral_image_c;

    if (ARCH_AARCH64)
        ff_nlmeans_init_aarch64(dsp);
}