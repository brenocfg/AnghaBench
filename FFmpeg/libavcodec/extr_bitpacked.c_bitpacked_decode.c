#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct BitpackedContext {int (* decode ) (TYPE_3__*,TYPE_2__*,TYPE_1__*) ;} ;
struct TYPE_11__ {struct BitpackedContext* priv_data; } ;
struct TYPE_10__ {int key_frame; int /*<<< orphan*/  pict_type; } ;
struct TYPE_9__ {int size; } ;
typedef  TYPE_1__ AVPacket ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_PICTURE_TYPE_I ; 
 int stub1 (TYPE_3__*,TYPE_2__*,TYPE_1__*) ; 

__attribute__((used)) static int bitpacked_decode(AVCodecContext *avctx, void *data, int *got_frame,
                            AVPacket *avpkt)
{
    struct BitpackedContext *bc = avctx->priv_data;
    int buf_size = avpkt->size;
    AVFrame *frame = data;
    int res;

    frame->pict_type = AV_PICTURE_TYPE_I;
    frame->key_frame = 1;

    res = bc->decode(avctx, frame, avpkt);
    if (res)
        return res;

    *got_frame = 1;
    return buf_size;

}