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
struct TYPE_6__ {int flags; TYPE_1__* priv_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  pc; } ;
typedef  int /*<<< orphan*/  ParseContext ;
typedef  TYPE_1__ DNXHDParserContext ;
typedef  TYPE_2__ AVCodecParserContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int PARSER_FLAG_COMPLETE_FRAMES ; 
 int dnxhd_find_frame_end (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ ff_combine_frame (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const**,int*) ; 

__attribute__((used)) static int dnxhd_parse(AVCodecParserContext *s,
                       AVCodecContext *avctx,
                       const uint8_t **poutbuf, int *poutbuf_size,
                       const uint8_t *buf, int buf_size)
{
    DNXHDParserContext *dctx = s->priv_data;
    ParseContext *pc = &dctx->pc;
    int next;

    if (s->flags & PARSER_FLAG_COMPLETE_FRAMES) {
        next = buf_size;
    } else {
        next = dnxhd_find_frame_end(dctx, buf, buf_size);
        if (ff_combine_frame(pc, next, &buf, &buf_size) < 0) {
            *poutbuf      = NULL;
            *poutbuf_size = 0;
            return buf_size;
        }
    }
    *poutbuf      = buf;
    *poutbuf_size = buf_size;
    return next;
}