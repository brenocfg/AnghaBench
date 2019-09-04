#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_6__ {int blocksize; TYPE_3__* subframes; } ;
struct TYPE_9__ {int channels; TYPE_1__ frame; } ;
struct TYPE_7__ {int /*<<< orphan*/  coding_mode; } ;
struct TYPE_8__ {int* samples; int wasted; int obits; TYPE_2__ rc; } ;
typedef  TYPE_3__ FlacSubframe ;
typedef  TYPE_4__ FlacEncodeContext ;

/* Variables and functions */
 int /*<<< orphan*/  CODING_MODE_RICE ; 
 int ff_ctz (int) ; 

__attribute__((used)) static void remove_wasted_bits(FlacEncodeContext *s)
{
    int ch, i;

    for (ch = 0; ch < s->channels; ch++) {
        FlacSubframe *sub = &s->frame.subframes[ch];
        int32_t v         = 0;

        for (i = 0; i < s->frame.blocksize; i++) {
            v |= sub->samples[i];
            if (v & 1)
                break;
        }

        if (v && !(v & 1)) {
            v = ff_ctz(v);

            for (i = 0; i < s->frame.blocksize; i++)
                sub->samples[i] >>= v;

            sub->wasted = v;
            sub->obits -= v;

            /* for 24-bit, check if removing wasted bits makes the range better
               suited for using RICE instead of RICE2 for entropy coding */
            if (sub->obits <= 17)
                sub->rc.coding_mode = CODING_MODE_RICE;
        }
    }
}