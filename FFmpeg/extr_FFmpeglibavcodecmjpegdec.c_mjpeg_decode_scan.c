#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_15__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int16_t ;
struct TYPE_25__ {int /*<<< orphan*/ ** data; } ;
struct TYPE_24__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_21__ {int /*<<< orphan*/  (* idct_put ) (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_20__ {int /*<<< orphan*/  (* clear_block ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_23__ {int bits; int mb_width; int mb_height; int width; int height; int* comp_index; int* linesize; int* coefs_finished; int* nb_blocks; int* h_scount; int* v_scount; int** quant_matrixes; size_t* quant_sindex; int* block_stride; int*** blocks; int /*<<< orphan*/  bottom_field; TYPE_15__* avctx; int /*<<< orphan*/ * dc_index; TYPE_5__ gb; int /*<<< orphan*/  block; TYPE_2__ idsp; int /*<<< orphan*/ * ac_index; TYPE_1__ bdsp; int /*<<< orphan*/  progressive; scalar_t__ interlaced; scalar_t__ restart_interval; scalar_t__ restart_count; TYPE_3__* picture_ptr; } ;
struct TYPE_22__ {int /*<<< orphan*/ ** data; } ;
struct TYPE_19__ {int lowres; int /*<<< orphan*/  pix_fmt; } ;
typedef  TYPE_4__ MJpegDecodeContext ;
typedef  TYPE_5__ GetBitContext ;
typedef  TYPE_6__ AVFrame ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AV_CEIL_RSHIFT (int,int) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int MAX_COMPONENTS ; 
 int /*<<< orphan*/  av_log (TYPE_15__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  av_pix_fmt_get_chroma_sub_sample (int /*<<< orphan*/ ,int*,int*) ; 
 scalar_t__ decode_block (TYPE_4__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ decode_dc_progressive (TYPE_4__*,int*,int,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  ff_dlog (TYPE_15__*,char*,int,int,...) ; 
 int get_bits1 (TYPE_5__*) ; 
 int /*<<< orphan*/  get_bits_left (TYPE_5__*) ; 
 int /*<<< orphan*/  handle_rstn (TYPE_4__*,int) ; 
 int /*<<< orphan*/  init_get_bits (TYPE_5__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  mjpeg_copy_block (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int) ; 
 int /*<<< orphan*/  shift_output (TYPE_4__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mjpeg_decode_scan(MJpegDecodeContext *s, int nb_components, int Ah,
                             int Al, const uint8_t *mb_bitmask,
                             int mb_bitmask_size,
                             const AVFrame *reference)
{
    int i, mb_x, mb_y, chroma_h_shift, chroma_v_shift, chroma_width, chroma_height;
    uint8_t *data[MAX_COMPONENTS];
    const uint8_t *reference_data[MAX_COMPONENTS];
    int linesize[MAX_COMPONENTS];
    GetBitContext mb_bitmask_gb = {0}; // initialize to silence gcc warning
    int bytes_per_pixel = 1 + (s->bits > 8);

    if (mb_bitmask) {
        if (mb_bitmask_size != (s->mb_width * s->mb_height + 7)>>3) {
            av_log(s->avctx, AV_LOG_ERROR, "mb_bitmask_size mismatches\n");
            return AVERROR_INVALIDDATA;
        }
        init_get_bits(&mb_bitmask_gb, mb_bitmask, s->mb_width * s->mb_height);
    }

    s->restart_count = 0;

    av_pix_fmt_get_chroma_sub_sample(s->avctx->pix_fmt, &chroma_h_shift,
                                     &chroma_v_shift);
    chroma_width  = AV_CEIL_RSHIFT(s->width,  chroma_h_shift);
    chroma_height = AV_CEIL_RSHIFT(s->height, chroma_v_shift);

    for (i = 0; i < nb_components; i++) {
        int c   = s->comp_index[i];
        data[c] = s->picture_ptr->data[c];
        reference_data[c] = reference ? reference->data[c] : NULL;
        linesize[c] = s->linesize[c];
        s->coefs_finished[c] |= 1;
    }

    for (mb_y = 0; mb_y < s->mb_height; mb_y++) {
        for (mb_x = 0; mb_x < s->mb_width; mb_x++) {
            const int copy_mb = mb_bitmask && !get_bits1(&mb_bitmask_gb);

            if (s->restart_interval && !s->restart_count)
                s->restart_count = s->restart_interval;

            if (get_bits_left(&s->gb) < 0) {
                av_log(s->avctx, AV_LOG_ERROR, "overread %d\n",
                       -get_bits_left(&s->gb));
                return AVERROR_INVALIDDATA;
            }
            for (i = 0; i < nb_components; i++) {
                uint8_t *ptr;
                int n, h, v, x, y, c, j;
                int block_offset;
                n = s->nb_blocks[i];
                c = s->comp_index[i];
                h = s->h_scount[i];
                v = s->v_scount[i];
                x = 0;
                y = 0;
                for (j = 0; j < n; j++) {
                    block_offset = (((linesize[c] * (v * mb_y + y) * 8) +
                                     (h * mb_x + x) * 8 * bytes_per_pixel) >> s->avctx->lowres);

                    if (s->interlaced && s->bottom_field)
                        block_offset += linesize[c] >> 1;
                    if (   8*(h * mb_x + x) < ((c == 1) || (c == 2) ? chroma_width  : s->width)
                        && 8*(v * mb_y + y) < ((c == 1) || (c == 2) ? chroma_height : s->height)) {
                        ptr = data[c] + block_offset;
                    } else
                        ptr = NULL;
                    if (!s->progressive) {
                        if (copy_mb) {
                            if (ptr)
                                mjpeg_copy_block(s, ptr, reference_data[c] + block_offset,
                                                linesize[c], s->avctx->lowres);

                        } else {
                            s->bdsp.clear_block(s->block);
                            if (decode_block(s, s->block, i,
                                             s->dc_index[i], s->ac_index[i],
                                             s->quant_matrixes[s->quant_sindex[i]]) < 0) {
                                av_log(s->avctx, AV_LOG_ERROR,
                                       "error y=%d x=%d\n", mb_y, mb_x);
                                return AVERROR_INVALIDDATA;
                            }
                            if (ptr) {
                                s->idsp.idct_put(ptr, linesize[c], s->block);
                                if (s->bits & 7)
                                    shift_output(s, ptr, linesize[c]);
                            }
                        }
                    } else {
                        int block_idx  = s->block_stride[c] * (v * mb_y + y) +
                                         (h * mb_x + x);
                        int16_t *block = s->blocks[c][block_idx];
                        if (Ah)
                            block[0] += get_bits1(&s->gb) *
                                        s->quant_matrixes[s->quant_sindex[i]][0] << Al;
                        else if (decode_dc_progressive(s, block, i, s->dc_index[i],
                                                       s->quant_matrixes[s->quant_sindex[i]],
                                                       Al) < 0) {
                            av_log(s->avctx, AV_LOG_ERROR,
                                   "error y=%d x=%d\n", mb_y, mb_x);
                            return AVERROR_INVALIDDATA;
                        }
                    }
                    ff_dlog(s->avctx, "mb: %d %d processed\n", mb_y, mb_x);
                    ff_dlog(s->avctx, "%d %d %d %d %d %d %d %d \n",
                            mb_x, mb_y, x, y, c, s->bottom_field,
                            (v * mb_y + y) * 8, (h * mb_x + x) * 8);
                    if (++x == h) {
                        x = 0;
                        y++;
                    }
                }
            }

            handle_rstn(s, nb_components);
        }
    }
    return 0;
}