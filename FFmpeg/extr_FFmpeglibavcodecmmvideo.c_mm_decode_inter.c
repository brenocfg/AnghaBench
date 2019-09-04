#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ buffer; scalar_t__ buffer_start; } ;
struct TYPE_12__ {TYPE_2__* frame; TYPE_1__* avctx; TYPE_4__ gb; } ;
struct TYPE_11__ {int** data; int* linesize; } ;
struct TYPE_10__ {int height; int width; } ;
typedef  TYPE_3__ MmContext ;
typedef  TYPE_4__ GetByteContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int bytestream2_get_byte (TYPE_4__*) ; 
 int bytestream2_get_bytes_left (TYPE_4__*) ; 
 int bytestream2_get_le16 (TYPE_4__*) ; 
 int /*<<< orphan*/  bytestream2_init (TYPE_4__*,scalar_t__,int) ; 

__attribute__((used)) static int mm_decode_inter(MmContext * s, int half_horiz, int half_vert)
{
    int data_off = bytestream2_get_le16(&s->gb);
    int y = 0;
    GetByteContext data_ptr;

    if (bytestream2_get_bytes_left(&s->gb) < data_off)
        return AVERROR_INVALIDDATA;

    bytestream2_init(&data_ptr, s->gb.buffer + data_off, bytestream2_get_bytes_left(&s->gb) - data_off);
    while (s->gb.buffer < data_ptr.buffer_start) {
        int i, j;
        int length = bytestream2_get_byte(&s->gb);
        int x = bytestream2_get_byte(&s->gb) + ((length & 0x80) << 1);
        length &= 0x7F;

        if (length==0) {
            y += x;
            continue;
        }

        if (y + half_vert >= s->avctx->height)
            return 0;

        for(i=0; i<length; i++) {
            int replace_array = bytestream2_get_byte(&s->gb);
            for(j=0; j<8; j++) {
                int replace = (replace_array >> (7-j)) & 1;
                if (x + half_horiz >= s->avctx->width)
                    return AVERROR_INVALIDDATA;
                if (replace) {
                    int color = bytestream2_get_byte(&data_ptr);
                    s->frame->data[0][y*s->frame->linesize[0] + x] = color;
                    if (half_horiz)
                        s->frame->data[0][y*s->frame->linesize[0] + x + 1] = color;
                    if (half_vert) {
                        s->frame->data[0][(y+1)*s->frame->linesize[0] + x] = color;
                        if (half_horiz)
                            s->frame->data[0][(y+1)*s->frame->linesize[0] + x + 1] = color;
                    }
                }
                x += 1 + half_horiz;
            }
        }

        y += 1 + half_vert;
    }

    return 0;
}