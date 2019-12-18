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
struct TYPE_6__ {int dpcm_direction; int mb_intra; size_t chroma_format; int /*<<< orphan*/  gb; int /*<<< orphan*/ ** dpcm_macroblock; int /*<<< orphan*/  avctx; int /*<<< orphan*/ ** block32; int /*<<< orphan*/  qscale; } ;
typedef  TYPE_1__ MpegEncContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int SLICE_END ; 
 int SLICE_OK ; 
 int /*<<< orphan*/  check_marker (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ get_bits1 (int /*<<< orphan*/ *) ; 
 unsigned int get_bits_left (int /*<<< orphan*/ *) ; 
 int* mpeg4_block_count ; 
 scalar_t__ mpeg4_decode_dpcm_macroblock (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mpeg4_decode_studio_block (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mpeg_get_qscale (TYPE_1__*) ; 
 int /*<<< orphan*/  next_start_code_studio (int /*<<< orphan*/ *) ; 
 scalar_t__ show_bits (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  skip_bits1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mpeg4_decode_studio_mb(MpegEncContext *s, int16_t block_[12][64])
{
    int i;

    s->dpcm_direction = 0;

    /* StudioMacroblock */
    /* Assumes I-VOP */
    s->mb_intra = 1;
    if (get_bits1(&s->gb)) { /* compression_mode */
        /* DCT */
        /* macroblock_type, 1 or 2-bit VLC */
        if (!get_bits1(&s->gb)) {
            skip_bits1(&s->gb);
            s->qscale = mpeg_get_qscale(s);
        }

        for (i = 0; i < mpeg4_block_count[s->chroma_format]; i++) {
            if (mpeg4_decode_studio_block(s, (*s->block32)[i], i) < 0)
                return AVERROR_INVALIDDATA;
        }
    } else {
        /* DPCM */
        check_marker(s->avctx, &s->gb, "DPCM block start");
        s->dpcm_direction = get_bits1(&s->gb) ? -1 : 1;
        for (i = 0; i < 3; i++) {
            if (mpeg4_decode_dpcm_macroblock(s, (*s->dpcm_macroblock)[i], i) < 0)
                return AVERROR_INVALIDDATA;
        }
    }

    if (get_bits_left(&s->gb) >= 24 && show_bits(&s->gb, 23) == 0) {
        next_start_code_studio(&s->gb);
        return SLICE_END;
    }

    //vcon-stp9L1.bits (first frame)
    if (get_bits_left(&s->gb) == 0)
        return SLICE_END;

    //vcon-stp2L1.bits, vcon-stp3L1.bits, vcon-stp6L1.bits, vcon-stp7L1.bits, vcon-stp8L1.bits, vcon-stp10L1.bits (first frame)
    if (get_bits_left(&s->gb) < 8U && show_bits(&s->gb, get_bits_left(&s->gb)) == 0)
        return SLICE_END;

    return SLICE_OK;
}