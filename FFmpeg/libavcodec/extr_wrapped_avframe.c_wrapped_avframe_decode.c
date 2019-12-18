#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int flags; int size; scalar_t__ data; } ;
typedef  TYPE_1__ AVPacket ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AV_PKT_FLAG_TRUSTED ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EPERM ; 
 int /*<<< orphan*/  av_frame_move_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_frame_unref (int /*<<< orphan*/ *) ; 
 int ff_attach_decode_data (int /*<<< orphan*/ *) ; 
 int ff_decode_frame_props (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wrapped_avframe_decode(AVCodecContext *avctx, void *data,
                                  int *got_frame, AVPacket *pkt)
{
    AVFrame *in, *out;
    int err;

    if (!(pkt->flags & AV_PKT_FLAG_TRUSTED)) {
        // This decoder is not usable with untrusted input.
        return AVERROR(EPERM);
    }

    if (pkt->size < sizeof(AVFrame))
        return AVERROR(EINVAL);

    in  = (AVFrame*)pkt->data;
    out = data;

    err = ff_decode_frame_props(avctx, out);
    if (err < 0)
        return err;

    av_frame_move_ref(out, in);

    err = ff_attach_decode_data(out);
    if (err < 0) {
        av_frame_unref(out);
        return err;
    }

    *got_frame = 1;
    return 0;
}