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
struct TYPE_4__ {int /*<<< orphan*/  compute_cache; int /*<<< orphan*/  compute_distance_ssd; } ;
typedef  TYPE_1__ AudioNLMDNDSPContext ;

/* Variables and functions */
 scalar_t__ ARCH_X86 ; 
 int /*<<< orphan*/  compute_cache_c ; 
 int /*<<< orphan*/  compute_distance_ssd_c ; 
 int /*<<< orphan*/  ff_anlmdn_init_x86 (TYPE_1__*) ; 

void ff_anlmdn_init(AudioNLMDNDSPContext *dsp)
{
    dsp->compute_distance_ssd = compute_distance_ssd_c;
    dsp->compute_cache        = compute_cache_c;

    if (ARCH_X86)
        ff_anlmdn_init_x86(dsp);
}