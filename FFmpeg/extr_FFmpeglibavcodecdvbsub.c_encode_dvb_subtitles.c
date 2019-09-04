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
typedef  int uint32_t ;
struct TYPE_8__ {int num_rects; TYPE_1__** rects; } ;
struct TYPE_7__ {int object_version; } ;
struct TYPE_6__ {int x; int y; int nb_colors; int w; int h; int /*<<< orphan*/  const** data; } ;
typedef  TYPE_2__ DVBSubtitleContext ;
typedef  TYPE_3__ AVSubtitle ;

/* Variables and functions */
 int /*<<< orphan*/  RGB_TO_U_CCIR (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RGB_TO_V_CCIR (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RGB_TO_Y_CCIR (int,int,int) ; 
 int /*<<< orphan*/  bytestream_put_be16 (int /*<<< orphan*/ **,int) ; 
 void dvb_encode_rle2 (int /*<<< orphan*/ **,int /*<<< orphan*/  const*,int,int,int) ; 
 void dvb_encode_rle4 (int /*<<< orphan*/ **,int /*<<< orphan*/  const*,int,int,int) ; 
 void dvb_encode_rle8 (int /*<<< orphan*/ **,int /*<<< orphan*/  const*,int,int,int) ; 

__attribute__((used)) static int encode_dvb_subtitles(DVBSubtitleContext *s,
                                uint8_t *outbuf, const AVSubtitle *h)
{
    uint8_t *q, *pseg_len;
    int page_id, region_id, clut_id, object_id, i, bpp_index, page_state;


    q = outbuf;

    page_id = 1;

    if (h->num_rects && !h->rects)
        return -1;

    /* page composition segment */

    *q++ = 0x0f; /* sync_byte */
    *q++ = 0x10; /* segment_type */
    bytestream_put_be16(&q, page_id);
    pseg_len = q;
    q += 2; /* segment length */
    *q++ = 30; /* page_timeout (seconds) */
    page_state = 2; /* mode change */
    /* page_version = 0 + page_state */
    *q++ = (s->object_version << 4) | (page_state << 2) | 3;

    for (region_id = 0; region_id < h->num_rects; region_id++) {
        *q++ = region_id;
        *q++ = 0xff; /* reserved */
        bytestream_put_be16(&q, h->rects[region_id]->x); /* left pos */
        bytestream_put_be16(&q, h->rects[region_id]->y); /* top pos */
    }

    bytestream_put_be16(&pseg_len, q - pseg_len - 2);

    if (h->num_rects) {
        for (clut_id = 0; clut_id < h->num_rects; clut_id++) {

            /* CLUT segment */

            if (h->rects[clut_id]->nb_colors <= 4) {
                /* 2 bpp, some decoders do not support it correctly */
                bpp_index = 0;
            } else if (h->rects[clut_id]->nb_colors <= 16) {
                /* 4 bpp, standard encoding */
                bpp_index = 1;
            } else if (h->rects[clut_id]->nb_colors <= 256) {
                /* 8 bpp, standard encoding */
                bpp_index = 2;
            } else {
                return -1;
            }


            /* CLUT segment */
            *q++ = 0x0f; /* sync byte */
            *q++ = 0x12; /* CLUT definition segment */
            bytestream_put_be16(&q, page_id);
            pseg_len = q;
            q += 2; /* segment length */
            *q++ = clut_id;
            *q++ = (0 << 4) | 0xf; /* version = 0 */

            for(i = 0; i < h->rects[clut_id]->nb_colors; i++) {
                *q++ = i; /* clut_entry_id */
                *q++ = (1 << (7 - bpp_index)) | (0xf << 1) | 1; /* 2 bits/pixel full range */
                {
                    int a, r, g, b;
                    uint32_t x= ((uint32_t*)h->rects[clut_id]->data[1])[i];
                    a = (x >> 24) & 0xff;
                    r = (x >> 16) & 0xff;
                    g = (x >>  8) & 0xff;
                    b = (x >>  0) & 0xff;

                    *q++ = RGB_TO_Y_CCIR(r, g, b);
                    *q++ = RGB_TO_V_CCIR(r, g, b, 0);
                    *q++ = RGB_TO_U_CCIR(r, g, b, 0);
                    *q++ = 255 - a;
                }
            }

            bytestream_put_be16(&pseg_len, q - pseg_len - 2);
        }
    }

    for (region_id = 0; region_id < h->num_rects; region_id++) {

        /* region composition segment */

        if (h->rects[region_id]->nb_colors <= 4) {
            /* 2 bpp, some decoders do not support it correctly */
            bpp_index = 0;
        } else if (h->rects[region_id]->nb_colors <= 16) {
            /* 4 bpp, standard encoding */
            bpp_index = 1;
        } else if (h->rects[region_id]->nb_colors <= 256) {
            /* 8 bpp, standard encoding */
            bpp_index = 2;
        } else {
            return -1;
        }

        *q++ = 0x0f; /* sync_byte */
        *q++ = 0x11; /* segment_type */
        bytestream_put_be16(&q, page_id);
        pseg_len = q;
        q += 2; /* segment length */
        *q++ = region_id;
        *q++ = (s->object_version << 4) | (0 << 3) | 0x07; /* version , no fill */
        bytestream_put_be16(&q, h->rects[region_id]->w); /* region width */
        bytestream_put_be16(&q, h->rects[region_id]->h); /* region height */
        *q++ = ((1 + bpp_index) << 5) | ((1 + bpp_index) << 2) | 0x03;
        *q++ = region_id; /* clut_id == region_id */
        *q++ = 0; /* 8 bit fill colors */
        *q++ = 0x03; /* 4 bit and 2 bit fill colors */

        bytestream_put_be16(&q, region_id); /* object_id == region_id */
        *q++ = (0 << 6) | (0 << 4);
        *q++ = 0;
        *q++ = 0xf0;
        *q++ = 0;

        bytestream_put_be16(&pseg_len, q - pseg_len - 2);
    }

    if (h->num_rects) {

        for (object_id = 0; object_id < h->num_rects; object_id++) {
            void (*dvb_encode_rle)(uint8_t **pq,
                                    const uint8_t *bitmap, int linesize,
                                    int w, int h);

            /* bpp_index maths */
            if (h->rects[object_id]->nb_colors <= 4) {
                /* 2 bpp, some decoders do not support it correctly */
                dvb_encode_rle = dvb_encode_rle2;
            } else if (h->rects[object_id]->nb_colors <= 16) {
                /* 4 bpp, standard encoding */
                dvb_encode_rle = dvb_encode_rle4;
            } else if (h->rects[object_id]->nb_colors <= 256) {
                /* 8 bpp, standard encoding */
                dvb_encode_rle = dvb_encode_rle8;
            } else {
                return -1;
            }

            /* Object Data segment */
            *q++ = 0x0f; /* sync byte */
            *q++ = 0x13;
            bytestream_put_be16(&q, page_id);
            pseg_len = q;
            q += 2; /* segment length */

            bytestream_put_be16(&q, object_id);
            *q++ = (s->object_version << 4) | (0 << 2) | (0 << 1) | 1; /* version = 0,
                                                                       onject_coding_method,
                                                                       non_modifying_color_flag */
            {
                uint8_t *ptop_field_len, *pbottom_field_len, *top_ptr, *bottom_ptr;

                ptop_field_len = q;
                q += 2;
                pbottom_field_len = q;
                q += 2;

                top_ptr = q;
                dvb_encode_rle(&q, h->rects[object_id]->data[0], h->rects[object_id]->w * 2,
                                    h->rects[object_id]->w, h->rects[object_id]->h >> 1);
                bottom_ptr = q;
                dvb_encode_rle(&q, h->rects[object_id]->data[0] + h->rects[object_id]->w,
                                    h->rects[object_id]->w * 2, h->rects[object_id]->w,
                                    h->rects[object_id]->h >> 1);

                bytestream_put_be16(&ptop_field_len, bottom_ptr - top_ptr);
                bytestream_put_be16(&pbottom_field_len, q - bottom_ptr);
            }

            bytestream_put_be16(&pseg_len, q - pseg_len - 2);
        }
    }

    /* end of display set segment */

    *q++ = 0x0f; /* sync_byte */
    *q++ = 0x80; /* segment_type */
    bytestream_put_be16(&q, page_id);
    pseg_len = q;
    q += 2; /* segment length */

    bytestream_put_be16(&pseg_len, q - pseg_len - 2);

    s->object_version = (s->object_version + 1) & 0xf;
    return q - outbuf;
}