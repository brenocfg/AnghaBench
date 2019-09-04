#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* new_cpl_coords; int new_cpl_leak; scalar_t__ cpl_in_use; scalar_t__* channel_in_cpl; } ;
struct TYPE_4__ {int fbw_channels; int num_blocks; TYPE_2__* blocks; } ;
typedef  TYPE_1__ AC3EncodeContext ;
typedef  TYPE_2__ AC3Block ;

/* Variables and functions */
 int AC3_MAX_CHANNELS ; 

void ff_eac3_set_cpl_states(AC3EncodeContext *s)
{
    int ch, blk;
    int first_cpl_coords[AC3_MAX_CHANNELS];

    /* set first cpl coords */
    for (ch = 1; ch <= s->fbw_channels; ch++)
        first_cpl_coords[ch] = 1;
    for (blk = 0; blk < s->num_blocks; blk++) {
        AC3Block *block = &s->blocks[blk];
        for (ch = 1; ch <= s->fbw_channels; ch++) {
            if (block->channel_in_cpl[ch]) {
                if (first_cpl_coords[ch]) {
                    block->new_cpl_coords[ch] = 2;
                    first_cpl_coords[ch]  = 0;
                }
            } else {
                first_cpl_coords[ch] = 1;
            }
        }
    }

    /* set first cpl leak */
    for (blk = 0; blk < s->num_blocks; blk++) {
        AC3Block *block = &s->blocks[blk];
        if (block->cpl_in_use) {
            block->new_cpl_leak = 2;
            break;
        }
    }
}