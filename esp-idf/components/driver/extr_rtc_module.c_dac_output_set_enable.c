#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t dac_channel_t ;
struct TYPE_4__ {TYPE_1__* pad_dac; } ;
struct TYPE_3__ {int dac_xpd_force; int xpd_dac; } ;

/* Variables and functions */
 size_t DAC_CHANNEL_1 ; 
 TYPE_2__ RTCIO ; 

__attribute__((used)) static inline void dac_output_set_enable(dac_channel_t channel, bool enable)
{
    RTCIO.pad_dac[channel-DAC_CHANNEL_1].dac_xpd_force = enable;
    RTCIO.pad_dac[channel-DAC_CHANNEL_1].xpd_dac = enable;
}