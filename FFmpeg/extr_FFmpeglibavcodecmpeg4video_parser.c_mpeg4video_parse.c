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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int flags; int /*<<< orphan*/ * priv_data; } ;
typedef  int /*<<< orphan*/  ParseContext ;
typedef  TYPE_1__ AVCodecParserContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int PARSER_FLAG_COMPLETE_FRAMES ; 
 scalar_t__ ff_combine_frame (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const**,int*) ; 
 int ff_mpeg4_find_frame_end (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  mpeg4_decode_header (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int mpeg4video_parse(AVCodecParserContext *s,
                            AVCodecContext *avctx,
                            const uint8_t **poutbuf, int *poutbuf_size,
                            const uint8_t *buf, int buf_size)
{
    ParseContext *pc = s->priv_data;
    int next;

    if (s->flags & PARSER_FLAG_COMPLETE_FRAMES) {
        next = buf_size;
    } else {
        next = ff_mpeg4_find_frame_end(pc, buf, buf_size);

        if (ff_combine_frame(pc, next, &buf, &buf_size) < 0) {
            *poutbuf      = NULL;
            *poutbuf_size = 0;
            return buf_size;
        }
    }
    mpeg4_decode_header(s, avctx, buf, buf_size);

    *poutbuf      = buf;
    *poutbuf_size = buf_size;
    return next;
}