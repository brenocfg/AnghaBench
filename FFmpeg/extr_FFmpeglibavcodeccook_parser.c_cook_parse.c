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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {int extradata_size; int channels; scalar_t__ extradata; } ;
struct TYPE_7__ {int duration; TYPE_1__* priv_data; } ;
struct TYPE_6__ {int duration; } ;
typedef  TYPE_1__ CookParseContext ;
typedef  TYPE_2__ AVCodecParserContext ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int AV_RB16 (scalar_t__) ; 

__attribute__((used)) static int cook_parse(AVCodecParserContext *s1, AVCodecContext *avctx,
                      const uint8_t **poutbuf, int *poutbuf_size,
                      const uint8_t *buf, int buf_size)
{
    CookParseContext *s = s1->priv_data;

    if (!s->duration &&
                avctx->extradata && avctx->extradata_size >= 8 && avctx->channels)
        s->duration = AV_RB16(avctx->extradata + 4) / avctx->channels;

    s1->duration = s->duration;

    /* always return the full packet. this parser isn't doing any splitting or
       combining, only setting packet duration */
    *poutbuf      = buf;
    *poutbuf_size = buf_size;
    return buf_size;
}