#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int ch_mask; } ;
typedef  TYPE_1__ DCACoreDecoder ;

/* Variables and functions */
 int DCA_SPEAKER_Ls ; 
 int DCA_SPEAKER_Lss ; 
 int DCA_SPEAKER_MASK_Ls ; 
 int DCA_SPEAKER_MASK_Rs ; 
 int DCA_SPEAKER_Rs ; 
 int DCA_SPEAKER_Rss ; 

__attribute__((used)) static inline int ff_dca_core_map_spkr(DCACoreDecoder *core, int spkr)
{
    if (core->ch_mask & (1U << spkr))
        return spkr;
    if (spkr == DCA_SPEAKER_Lss && (core->ch_mask & DCA_SPEAKER_MASK_Ls))
        return DCA_SPEAKER_Ls;
    if (spkr == DCA_SPEAKER_Rss && (core->ch_mask & DCA_SPEAKER_MASK_Rs))
        return DCA_SPEAKER_Rs;
    return -1;
}