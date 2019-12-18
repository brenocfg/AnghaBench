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
typedef  int /*<<< orphan*/  RV34VLC ;

/* Variables and functions */
 size_t av_clip (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * inter_vlcs ; 
 int /*<<< orphan*/ * intra_vlcs ; 
 size_t** rv34_quant_to_vlc_set ; 

__attribute__((used)) static inline RV34VLC* choose_vlc_set(int quant, int mod, int type)
{
    if(mod == 2 && quant < 19) quant += 10;
    else if(mod && quant < 26) quant += 5;
    return type ? &inter_vlcs[rv34_quant_to_vlc_set[1][av_clip(quant, 0, 30)]]
                : &intra_vlcs[rv34_quant_to_vlc_set[0][av_clip(quant, 0, 30)]];
}