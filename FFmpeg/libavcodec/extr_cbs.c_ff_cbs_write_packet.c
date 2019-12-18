#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; int /*<<< orphan*/ * buf; } ;
struct TYPE_6__ {int /*<<< orphan*/  data_size; int /*<<< orphan*/  data; int /*<<< orphan*/  data_ref; } ;
typedef  TYPE_1__ CodedBitstreamFragment ;
typedef  int /*<<< orphan*/  CodedBitstreamContext ;
typedef  TYPE_2__ AVPacket ;
typedef  int /*<<< orphan*/  AVBufferRef ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/ * av_buffer_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ **) ; 
 int ff_cbs_write_fragment_data (int /*<<< orphan*/ *,TYPE_1__*) ; 

int ff_cbs_write_packet(CodedBitstreamContext *ctx,
                        AVPacket *pkt,
                        CodedBitstreamFragment *frag)
{
    AVBufferRef *buf;
    int err;

    err = ff_cbs_write_fragment_data(ctx, frag);
    if (err < 0)
        return err;

    buf = av_buffer_ref(frag->data_ref);
    if (!buf)
        return AVERROR(ENOMEM);

    av_buffer_unref(&pkt->buf);

    pkt->buf  = buf;
    pkt->data = frag->data;
    pkt->size = frag->data_size;

    return 0;
}