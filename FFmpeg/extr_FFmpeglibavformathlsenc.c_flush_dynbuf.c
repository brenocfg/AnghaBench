#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/  out; TYPE_2__* avf; } ;
typedef  TYPE_1__ VariantStream ;
struct TYPE_6__ {int /*<<< orphan*/ * pb; } ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_write_frame (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int avio_close_dyn_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  avio_flush (int /*<<< orphan*/ *) ; 
 int avio_open_dyn_buf (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int flush_dynbuf(VariantStream *vs, int *range_length)
{
    AVFormatContext *ctx = vs->avf;
    uint8_t *buffer;

    if (!ctx->pb) {
        return AVERROR(EINVAL);
    }

    // flush
    av_write_frame(ctx, NULL);
    avio_flush(ctx->pb);

    // write out to file
    *range_length = avio_close_dyn_buf(ctx->pb, &buffer);
    ctx->pb = NULL;
    avio_write(vs->out, buffer, *range_length);
    av_free(buffer);

    // re-open buffer
    return avio_open_dyn_buf(&ctx->pb);
}