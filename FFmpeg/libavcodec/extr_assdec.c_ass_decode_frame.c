#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  ass; int /*<<< orphan*/  type; } ;
struct TYPE_7__ {scalar_t__ size; int /*<<< orphan*/  data; } ;
struct TYPE_6__ {int num_rects; TYPE_3__** rects; } ;
typedef  TYPE_1__ AVSubtitle ;
typedef  TYPE_2__ AVPacket ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  SUBTITLE_ASS ; 
 TYPE_3__** av_malloc (int) ; 
 TYPE_3__* av_mallocz (int) ; 
 int /*<<< orphan*/  av_strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ass_decode_frame(AVCodecContext *avctx, void *data, int *got_sub_ptr,
                            AVPacket *avpkt)
{
    AVSubtitle *sub = data;

    if (avpkt->size <= 0)
        return avpkt->size;

    sub->rects = av_malloc(sizeof(*sub->rects));
    if (!sub->rects)
        return AVERROR(ENOMEM);
    sub->rects[0] = av_mallocz(sizeof(*sub->rects[0]));
    if (!sub->rects[0])
        return AVERROR(ENOMEM);
    sub->num_rects = 1;
    sub->rects[0]->type = SUBTITLE_ASS;
    sub->rects[0]->ass  = av_strdup(avpkt->data);
    if (!sub->rects[0]->ass)
        return AVERROR(ENOMEM);
    *got_sub_ptr = 1;
    return avpkt->size;
}