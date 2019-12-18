#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ last_index; } ;
struct TYPE_7__ {TYPE_1__ parse_context; TYPE_2__* avctx; scalar_t__ divx_packed; int /*<<< orphan*/  gb; } ;
struct TYPE_6__ {int flags; scalar_t__ hwaccel; } ;
typedef  TYPE_3__ MpegEncContext ;

/* Variables and functions */
 int AV_CODEC_FLAG_TRUNCATED ; 
 int get_bits_count (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_consumed_bytes(MpegEncContext *s, int buf_size)
{
    int pos = (get_bits_count(&s->gb) + 7) >> 3;

    if (s->divx_packed || s->avctx->hwaccel) {
        /* We would have to scan through the whole buf to handle the weird
         * reordering ... */
        return buf_size;
    } else if (s->avctx->flags & AV_CODEC_FLAG_TRUNCATED) {
        pos -= s->parse_context.last_index;
        // padding is not really read so this might be -1
        if (pos < 0)
            pos = 0;
        return pos;
    } else {
        // avoid infinite loops (maybe not needed...)
        if (pos == 0)
            pos = 1;
        // oops ;)
        if (pos + 10 > buf_size)
            pos = buf_size;

        return pos;
    }
}