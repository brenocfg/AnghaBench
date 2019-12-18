#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int flushing; int /*<<< orphan*/  refcount; int /*<<< orphan*/  surface; } ;
typedef  TYPE_1__ MediaCodecDecContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int atomic_load (int /*<<< orphan*/ *) ; 
 int mediacodec_dec_flush_codec (int /*<<< orphan*/ *,TYPE_1__*) ; 

int ff_mediacodec_dec_flush(AVCodecContext *avctx, MediaCodecDecContext *s)
{
    if (!s->surface || atomic_load(&s->refcount) == 1) {
        int ret;

        /* No frames (holding a reference to the codec) are retained by the
         * user, thus we can flush the codec and returns accordingly */
        if ((ret = mediacodec_dec_flush_codec(avctx, s)) < 0) {
            return ret;
        }

        return 1;
    }

    s->flushing = 1;
    return 0;
}