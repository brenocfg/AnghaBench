#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  readorder; int /*<<< orphan*/  keep_ass_markup; int /*<<< orphan*/  linebreaks; } ;
typedef  TYPE_1__ TextContext ;
struct TYPE_16__ {int /*<<< orphan*/  str; } ;
struct TYPE_15__ {TYPE_1__* priv_data; } ;
struct TYPE_14__ {char* data; scalar_t__ size; } ;
struct TYPE_13__ {scalar_t__ num_rects; } ;
typedef  TYPE_2__ AVSubtitle ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVCodecContext ;
typedef  TYPE_5__ AVBPrint ;

/* Variables and functions */
 int /*<<< orphan*/  AV_BPRINT_SIZE_UNLIMITED ; 
 int /*<<< orphan*/  av_bprint_finalize (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_bprint_init (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ff_ass_add_rect (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_ass_bprint_text_event (TYPE_5__*,char const*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int text_decode_frame(AVCodecContext *avctx, void *data,
                             int *got_sub_ptr, AVPacket *avpkt)
{
    int ret = 0;
    AVBPrint buf;
    AVSubtitle *sub = data;
    const char *ptr = avpkt->data;
    TextContext *text = avctx->priv_data;

    av_bprint_init(&buf, 0, AV_BPRINT_SIZE_UNLIMITED);
    if (ptr && avpkt->size > 0 && *ptr) {
        ff_ass_bprint_text_event(&buf, ptr, avpkt->size, text->linebreaks, text->keep_ass_markup);
        ret = ff_ass_add_rect(sub, buf.str, text->readorder++, 0, NULL, NULL);
    }
    av_bprint_finalize(&buf, NULL);
    if (ret < 0)
        return ret;
    *got_sub_ptr = sub->num_rects > 0;
    return avpkt->size;
}