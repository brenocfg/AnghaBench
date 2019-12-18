#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int nb_samples; scalar_t__* extended_data; } ;
struct TYPE_14__ {TYPE_8__* frame; TYPE_2__** output_element; TYPE_3__*** che; } ;
struct TYPE_13__ {int channels; TYPE_5__* priv_data; } ;
struct TYPE_12__ {TYPE_1__* ch; } ;
struct TYPE_11__ {int /*<<< orphan*/ * ret; } ;
struct TYPE_10__ {int /*<<< orphan*/  ret_buf; int /*<<< orphan*/  ret; } ;
typedef  int /*<<< orphan*/  INTFLOAT ;
typedef  TYPE_3__ ChannelElement ;
typedef  TYPE_4__ AVCodecContext ;
typedef  TYPE_5__ AACContext ;

/* Variables and functions */
 int MAX_ELEM_ID ; 
 int /*<<< orphan*/  av_frame_unref (TYPE_8__*) ; 
 int ff_get_buffer (TYPE_4__*,TYPE_8__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int frame_configure_elements(AVCodecContext *avctx)
{
    AACContext *ac = avctx->priv_data;
    int type, id, ch, ret;

    /* set channel pointers to internal buffers by default */
    for (type = 0; type < 4; type++) {
        for (id = 0; id < MAX_ELEM_ID; id++) {
            ChannelElement *che = ac->che[type][id];
            if (che) {
                che->ch[0].ret = che->ch[0].ret_buf;
                che->ch[1].ret = che->ch[1].ret_buf;
            }
        }
    }

    /* get output buffer */
    av_frame_unref(ac->frame);
    if (!avctx->channels)
        return 1;

    ac->frame->nb_samples = 2048;
    if ((ret = ff_get_buffer(avctx, ac->frame, 0)) < 0)
        return ret;

    /* map output channel pointers to AVFrame data */
    for (ch = 0; ch < avctx->channels; ch++) {
        if (ac->output_element[ch])
            ac->output_element[ch]->ret = (INTFLOAT *)ac->frame->extended_data[ch];
    }

    return 0;
}