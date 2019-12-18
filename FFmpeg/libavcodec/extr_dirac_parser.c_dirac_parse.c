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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {int flags; TYPE_1__* priv_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  is_synced; } ;
typedef  TYPE_1__ DiracParseContext ;
typedef  TYPE_2__ AVCodecParserContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int PARSER_FLAG_COMPLETE_FRAMES ; 
 scalar_t__ dirac_combine_frame (TYPE_2__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const**,int*) ; 
 int find_frame_end (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int dirac_parse(AVCodecParserContext *s, AVCodecContext *avctx,
                       const uint8_t **poutbuf, int *poutbuf_size,
                       const uint8_t *buf, int buf_size)
{
    DiracParseContext *pc = s->priv_data;
    int next;

    *poutbuf      = NULL;
    *poutbuf_size = 0;

    if (s->flags & PARSER_FLAG_COMPLETE_FRAMES) {
        next          = buf_size;
        *poutbuf      = buf;
        *poutbuf_size = buf_size;
        /* Assume that data has been packetized into an encapsulation unit. */
    } else {
        next = find_frame_end(pc, buf, buf_size);
        if (!pc->is_synced && next == -1)
            /* No frame start found yet. So throw away the entire buffer. */
            return buf_size;

        if (dirac_combine_frame(s, avctx, next, &buf, &buf_size) < 0)
            return buf_size;
    }

    *poutbuf      = buf;
    *poutbuf_size = buf_size;
    return next;
}