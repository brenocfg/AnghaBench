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
typedef  int uint8_t ;
struct TYPE_6__ {scalar_t__ codec_id; } ;
struct TYPE_5__ {void* pict_type; } ;
typedef  TYPE_1__ AVCodecParserContext ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_THEORA ; 
 void* AV_PICTURE_TYPE_I ; 
 void* AV_PICTURE_TYPE_P ; 

__attribute__((used)) static int parse(AVCodecParserContext *s,
                 AVCodecContext *avctx,
                 const uint8_t **poutbuf, int *poutbuf_size,
                 const uint8_t *buf, int buf_size)
{
    if (avctx->codec_id == AV_CODEC_ID_THEORA)
        s->pict_type = (buf[0] & 0x40) ? AV_PICTURE_TYPE_P : AV_PICTURE_TYPE_I;
    else
        s->pict_type = (buf[0] & 0x80) ? AV_PICTURE_TYPE_P : AV_PICTURE_TYPE_I;

    *poutbuf      = buf;
    *poutbuf_size = buf_size;
    return buf_size;
}