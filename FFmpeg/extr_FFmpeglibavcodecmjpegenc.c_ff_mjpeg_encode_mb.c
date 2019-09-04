#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_6__ {scalar_t__ huffman; scalar_t__ chroma_format; int mb_x; int width; int /*<<< orphan*/  i_tex_bits; } ;
typedef  TYPE_1__ MpegEncContext ;

/* Variables and functions */
 scalar_t__ CHROMA_420 ; 
 scalar_t__ CHROMA_444 ; 
 scalar_t__ HUFFMAN_TABLE_OPTIMAL ; 
 int /*<<< orphan*/  encode_block (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ get_bits_diff (TYPE_1__*) ; 
 int /*<<< orphan*/  record_block (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

void ff_mjpeg_encode_mb(MpegEncContext *s, int16_t block[12][64])
{
    int i;
    if (s->huffman == HUFFMAN_TABLE_OPTIMAL) {
        if (s->chroma_format == CHROMA_444) {
            record_block(s, block[0], 0);
            record_block(s, block[2], 2);
            record_block(s, block[4], 4);
            record_block(s, block[8], 8);
            record_block(s, block[5], 5);
            record_block(s, block[9], 9);

            if (16*s->mb_x+8 < s->width) {
                record_block(s, block[1], 1);
                record_block(s, block[3], 3);
                record_block(s, block[6], 6);
                record_block(s, block[10], 10);
                record_block(s, block[7], 7);
                record_block(s, block[11], 11);
            }
        } else {
            for(i=0;i<5;i++) {
                record_block(s, block[i], i);
            }
            if (s->chroma_format == CHROMA_420) {
                record_block(s, block[5], 5);
            } else {
                record_block(s, block[6], 6);
                record_block(s, block[5], 5);
                record_block(s, block[7], 7);
            }
        }
    } else {
        if (s->chroma_format == CHROMA_444) {
            encode_block(s, block[0], 0);
            encode_block(s, block[2], 2);
            encode_block(s, block[4], 4);
            encode_block(s, block[8], 8);
            encode_block(s, block[5], 5);
            encode_block(s, block[9], 9);

            if (16*s->mb_x+8 < s->width) {
                encode_block(s, block[1], 1);
                encode_block(s, block[3], 3);
                encode_block(s, block[6], 6);
                encode_block(s, block[10], 10);
                encode_block(s, block[7], 7);
                encode_block(s, block[11], 11);
            }
        } else {
            for(i=0;i<5;i++) {
                encode_block(s, block[i], i);
            }
            if (s->chroma_format == CHROMA_420) {
                encode_block(s, block[5], 5);
            } else {
                encode_block(s, block[6], 6);
                encode_block(s, block[5], 5);
                encode_block(s, block[7], 7);
            }
        }

        s->i_tex_bits += get_bits_diff(s);
    }
}