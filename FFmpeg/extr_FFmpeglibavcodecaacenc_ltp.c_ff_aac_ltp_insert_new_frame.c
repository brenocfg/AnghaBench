#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int* chan_map; int /*<<< orphan*/ ** planar_samples; TYPE_4__* cpe; } ;
struct TYPE_10__ {TYPE_3__* ch; } ;
struct TYPE_7__ {scalar_t__ lag; } ;
struct TYPE_8__ {TYPE_1__ ltp; } ;
struct TYPE_9__ {TYPE_2__ ics; int /*<<< orphan*/ * ret_buf; int /*<<< orphan*/ * ltp_state; } ;
typedef  TYPE_3__ SingleChannelElement ;
typedef  TYPE_4__ ChannelElement ;
typedef  TYPE_5__ AACEncContext ;

/* Variables and functions */
 int TYPE_CPE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void ff_aac_ltp_insert_new_frame(AACEncContext *s)
{
    int i, ch, tag, chans, cur_channel, start_ch = 0;
    ChannelElement *cpe;
    SingleChannelElement *sce;
    for (i = 0; i < s->chan_map[0]; i++) {
        cpe = &s->cpe[i];
        tag      = s->chan_map[i+1];
        chans    = tag == TYPE_CPE ? 2 : 1;
        for (ch = 0; ch < chans; ch++) {
            sce = &cpe->ch[ch];
            cur_channel = start_ch + ch;
            /* New sample + overlap */
            memcpy(&sce->ltp_state[0],    &sce->ltp_state[1024], 1024*sizeof(sce->ltp_state[0]));
            memcpy(&sce->ltp_state[1024], &s->planar_samples[cur_channel][2048], 1024*sizeof(sce->ltp_state[0]));
            memcpy(&sce->ltp_state[2048], &sce->ret_buf[0], 1024*sizeof(sce->ltp_state[0]));
            sce->ics.ltp.lag = 0;
        }
        start_ch += chans;
    }
}