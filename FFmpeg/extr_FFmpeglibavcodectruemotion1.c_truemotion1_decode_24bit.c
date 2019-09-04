#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int flags; unsigned char* mb_change_bits; unsigned int* vert_pred; int block_width; TYPE_2__* frame; int /*<<< orphan*/  mb_change_bits_row_size; int /*<<< orphan*/  block_type; TYPE_1__* avctx; } ;
typedef  TYPE_3__ TrueMotion1Context ;
struct TYPE_6__ {unsigned char** data; int /*<<< orphan*/ * linesize; } ;
struct TYPE_5__ {int width; int height; } ;

/* Variables and functions */
 int /*<<< orphan*/  APPLY_C_PREDICTOR_24 () ; 
 int /*<<< orphan*/  APPLY_Y_PREDICTOR_24 () ; 
 int /*<<< orphan*/  BLOCK_2x2 ; 
 int /*<<< orphan*/  BLOCK_4x2 ; 
 int FLAG_KEYFRAME ; 
 int /*<<< orphan*/  GET_NEXT_INDEX () ; 
 int /*<<< orphan*/  OUTPUT_PIXEL_PAIR () ; 
 int /*<<< orphan*/  memset (unsigned int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void truemotion1_decode_24bit(TrueMotion1Context *s)
{
    int y;
    int pixels_left;  /* remaining pixels on this line */
    unsigned int predictor_pair;
    unsigned int horiz_pred;
    unsigned int *vert_pred;
    unsigned int *current_pixel_pair;
    unsigned char *current_line = s->frame->data[0];
    int keyframe = s->flags & FLAG_KEYFRAME;

    /* these variables are for managing the stream of macroblock change bits */
    const unsigned char *mb_change_bits = s->mb_change_bits;
    unsigned char mb_change_byte;
    unsigned char mb_change_byte_mask;
    int mb_change_index;

    /* these variables are for managing the main index stream */
    int index_stream_index = 0;  /* yes, the index into the index stream */
    int index;

    /* clean out the line buffer */
    memset(s->vert_pred, 0, s->avctx->width * sizeof(unsigned int));

    GET_NEXT_INDEX();

    for (y = 0; y < s->avctx->height; y++) {

        /* re-init variables for the next line iteration */
        horiz_pred = 0;
        current_pixel_pair = (unsigned int *)current_line;
        vert_pred = s->vert_pred;
        mb_change_index = 0;
        mb_change_byte = mb_change_bits[mb_change_index++];
        mb_change_byte_mask = 0x01;
        pixels_left = s->avctx->width;

        while (pixels_left > 0) {

            if (keyframe || ((mb_change_byte & mb_change_byte_mask) == 0)) {

                switch (y & 3) {
                case 0:
                    /* if macroblock width is 2, apply C-Y-C-Y; else
                     * apply C-Y-Y */
                    if (s->block_width == 2) {
                        APPLY_C_PREDICTOR_24();
                        APPLY_Y_PREDICTOR_24();
                        OUTPUT_PIXEL_PAIR();
                        APPLY_C_PREDICTOR_24();
                        APPLY_Y_PREDICTOR_24();
                        OUTPUT_PIXEL_PAIR();
                    } else {
                        APPLY_C_PREDICTOR_24();
                        APPLY_Y_PREDICTOR_24();
                        OUTPUT_PIXEL_PAIR();
                        APPLY_Y_PREDICTOR_24();
                        OUTPUT_PIXEL_PAIR();
                    }
                    break;

                case 1:
                case 3:
                    /* always apply 2 Y predictors on these iterations */
                    APPLY_Y_PREDICTOR_24();
                    OUTPUT_PIXEL_PAIR();
                    APPLY_Y_PREDICTOR_24();
                    OUTPUT_PIXEL_PAIR();
                    break;

                case 2:
                    /* this iteration might be C-Y-C-Y, Y-Y, or C-Y-Y
                     * depending on the macroblock type */
                    if (s->block_type == BLOCK_2x2) {
                        APPLY_C_PREDICTOR_24();
                        APPLY_Y_PREDICTOR_24();
                        OUTPUT_PIXEL_PAIR();
                        APPLY_C_PREDICTOR_24();
                        APPLY_Y_PREDICTOR_24();
                        OUTPUT_PIXEL_PAIR();
                    } else if (s->block_type == BLOCK_4x2) {
                        APPLY_C_PREDICTOR_24();
                        APPLY_Y_PREDICTOR_24();
                        OUTPUT_PIXEL_PAIR();
                        APPLY_Y_PREDICTOR_24();
                        OUTPUT_PIXEL_PAIR();
                    } else {
                        APPLY_Y_PREDICTOR_24();
                        OUTPUT_PIXEL_PAIR();
                        APPLY_Y_PREDICTOR_24();
                        OUTPUT_PIXEL_PAIR();
                    }
                    break;
                }

            } else {

                /* skip (copy) four pixels, but reassign the horizontal
                 * predictor */
                *vert_pred++ = *current_pixel_pair++;
                horiz_pred = *current_pixel_pair - *vert_pred;
                *vert_pred++ = *current_pixel_pair++;

            }

            if (!keyframe) {
                mb_change_byte_mask <<= 1;

                /* next byte */
                if (!mb_change_byte_mask) {
                    mb_change_byte = mb_change_bits[mb_change_index++];
                    mb_change_byte_mask = 0x01;
                }
            }

            pixels_left -= 2;
        }

        /* next change row */
        if (((y + 1) & 3) == 0)
            mb_change_bits += s->mb_change_bits_row_size;

        current_line += s->frame->linesize[0];
    }
}