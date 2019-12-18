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
typedef  int uint8_t ;
struct TYPE_8__ {int /*<<< orphan*/  channels; } ;
struct TYPE_7__ {int duration; TYPE_1__* priv_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  pc; } ;
typedef  int /*<<< orphan*/  ParseContext ;
typedef  TYPE_1__ G723_1ParseContext ;
typedef  TYPE_2__ AVCodecParserContext ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int END_NOT_FOUND ; 
 int FFMAX (int,int /*<<< orphan*/ ) ; 
 scalar_t__ ff_combine_frame (int /*<<< orphan*/ *,int,int const**,int*) ; 
 int* frame_size ; 

__attribute__((used)) static int g723_1_parse(AVCodecParserContext *s1, AVCodecContext *avctx,
                        const uint8_t **poutbuf, int *poutbuf_size,
                        const uint8_t *buf, int buf_size)
{
    G723_1ParseContext *s = s1->priv_data;
    ParseContext *pc = &s->pc;
    int next = END_NOT_FOUND;

    if (buf_size > 0)
        next = frame_size[buf[0] & 3] * FFMAX(1, avctx->channels);

    if (ff_combine_frame(pc, next, &buf, &buf_size) < 0 || !buf_size) {
        *poutbuf      = NULL;
        *poutbuf_size = 0;
        return buf_size;
    }

    s1->duration = 240;

    *poutbuf      = buf;
    *poutbuf_size = buf_size;
    return next;
}