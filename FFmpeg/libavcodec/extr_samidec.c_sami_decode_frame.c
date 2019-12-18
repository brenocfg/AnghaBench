#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_2__* priv_data; } ;
struct TYPE_13__ {char* data; scalar_t__ size; } ;
struct TYPE_12__ {scalar_t__ num_rects; } ;
struct TYPE_10__ {int /*<<< orphan*/  str; } ;
struct TYPE_11__ {int /*<<< orphan*/  readorder; TYPE_1__ full; } ;
typedef  TYPE_2__ SAMIContext ;
typedef  TYPE_3__ AVSubtitle ;
typedef  TYPE_4__ AVPacket ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int ff_ass_add_rect (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sami_paragraph_to_ass (TYPE_5__*,char const*) ; 

__attribute__((used)) static int sami_decode_frame(AVCodecContext *avctx,
                             void *data, int *got_sub_ptr, AVPacket *avpkt)
{
    AVSubtitle *sub = data;
    const char *ptr = avpkt->data;
    SAMIContext *sami = avctx->priv_data;

    if (ptr && avpkt->size > 0) {
        int ret = sami_paragraph_to_ass(avctx, ptr);
        if (ret < 0)
            return ret;
        // TODO: pass escaped sami->encoded_source.str as source
        ret = ff_ass_add_rect(sub, sami->full.str, sami->readorder++, 0, NULL, NULL);
        if (ret < 0)
            return ret;
    }
    *got_sub_ptr = sub->num_rects > 0;
    return avpkt->size;
}