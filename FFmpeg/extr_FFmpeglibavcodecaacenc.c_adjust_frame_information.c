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
struct TYPE_9__ {int ms_mode; scalar_t__* ms_mask; TYPE_2__* ch; scalar_t__ common_window; } ;
struct TYPE_8__ {int num_windows; int* group_len; int num_swb; int max_sfb; } ;
struct TYPE_6__ {scalar_t__ num_pulse; } ;
struct TYPE_7__ {int* zeroes; TYPE_3__ ics; TYPE_1__ pulse; } ;
typedef  TYPE_3__ IndividualChannelStream ;
typedef  TYPE_4__ ChannelElement ;

/* Variables and functions */
 void* FFMAX (int,int) ; 

__attribute__((used)) static void adjust_frame_information(ChannelElement *cpe, int chans)
{
    int i, w, w2, g, ch;
    int maxsfb, cmaxsfb;

    for (ch = 0; ch < chans; ch++) {
        IndividualChannelStream *ics = &cpe->ch[ch].ics;
        maxsfb = 0;
        cpe->ch[ch].pulse.num_pulse = 0;
        for (w = 0; w < ics->num_windows; w += ics->group_len[w]) {
            for (w2 =  0; w2 < ics->group_len[w]; w2++) {
                for (cmaxsfb = ics->num_swb; cmaxsfb > 0 && cpe->ch[ch].zeroes[w*16+cmaxsfb-1]; cmaxsfb--)
                    ;
                maxsfb = FFMAX(maxsfb, cmaxsfb);
            }
        }
        ics->max_sfb = maxsfb;

        //adjust zero bands for window groups
        for (w = 0; w < ics->num_windows; w += ics->group_len[w]) {
            for (g = 0; g < ics->max_sfb; g++) {
                i = 1;
                for (w2 = w; w2 < w + ics->group_len[w]; w2++) {
                    if (!cpe->ch[ch].zeroes[w2*16 + g]) {
                        i = 0;
                        break;
                    }
                }
                cpe->ch[ch].zeroes[w*16 + g] = i;
            }
        }
    }

    if (chans > 1 && cpe->common_window) {
        IndividualChannelStream *ics0 = &cpe->ch[0].ics;
        IndividualChannelStream *ics1 = &cpe->ch[1].ics;
        int msc = 0;
        ics0->max_sfb = FFMAX(ics0->max_sfb, ics1->max_sfb);
        ics1->max_sfb = ics0->max_sfb;
        for (w = 0; w < ics0->num_windows*16; w += 16)
            for (i = 0; i < ics0->max_sfb; i++)
                if (cpe->ms_mask[w+i])
                    msc++;
        if (msc == 0 || ics0->max_sfb == 0)
            cpe->ms_mode = 0;
        else
            cpe->ms_mode = msc < ics0->max_sfb * ics0->num_windows ? 1 : 2;
    }
}