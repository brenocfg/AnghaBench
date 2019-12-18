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
struct TYPE_8__ {scalar_t__ codec_id; } ;
struct TYPE_7__ {scalar_t__ pts; int /*<<< orphan*/  pict_type; TYPE_1__* priv_data; } ;
struct TYPE_6__ {scalar_t__ key_dts; int key_pts; } ;
typedef  TYPE_1__ RV34ParseContext ;
typedef  TYPE_2__ AVCodecParserContext ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_RV30 ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 int AV_RB32 (int const*) ; 
 int /*<<< orphan*/ * rv_to_av_frame_type ; 

__attribute__((used)) static int rv34_parse(AVCodecParserContext *s,
                      AVCodecContext *avctx,
                      const uint8_t **poutbuf, int *poutbuf_size,
                      const uint8_t *buf, int buf_size)
{
    RV34ParseContext *pc = s->priv_data;
    int type, pts, hdr;

    if (buf_size < 13 + *buf * 8) {
        *poutbuf = buf;
        *poutbuf_size = buf_size;
        return buf_size;
    }

    hdr = AV_RB32(buf + 9 + *buf * 8);
    if (avctx->codec_id == AV_CODEC_ID_RV30) {
        type = (hdr >> 27) & 3;
        pts  = (hdr >>  7) & 0x1FFF;
    } else {
        type = (hdr >> 29) & 3;
        pts  = (hdr >>  6) & 0x1FFF;
    }

    if (type != 3 && s->pts != AV_NOPTS_VALUE) {
        pc->key_dts = s->pts;
        pc->key_pts = pts;
    } else {
        if (type != 3)
            s->pts = pc->key_dts + ((pts - pc->key_pts) & 0x1FFF);
        else
            s->pts = pc->key_dts - ((pc->key_pts - pts) & 0x1FFF);
    }
    s->pict_type = rv_to_av_frame_type[type];

    *poutbuf = buf;
    *poutbuf_size = buf_size;
    return buf_size;
}