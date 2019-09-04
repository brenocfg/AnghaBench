#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  idct_permutation; } ;
struct TYPE_10__ {scalar_t__ pict_type; int progressive_frame; int alternate_scan; int frame_pred_frame_dct; int q_scale_type; int /*<<< orphan*/  intra_v_scantable; TYPE_1__ idsp; int /*<<< orphan*/  intra_h_scantable; int /*<<< orphan*/  intra_scantable; int /*<<< orphan*/  inter_scantable; scalar_t__ intra_dc_precision; scalar_t__ dct_precision; int /*<<< orphan*/  decode_mb; scalar_t__ interlaced_dct; scalar_t__ partitioned_frame; } ;
struct TYPE_11__ {scalar_t__ shape; TYPE_2__ m; } ;
typedef  TYPE_2__ MpegEncContext ;
typedef  TYPE_3__ Mpeg4DecContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 scalar_t__ AV_PICTURE_TYPE_I ; 
 scalar_t__ BIN_ONLY_SHAPE ; 
 int /*<<< orphan*/  decode_smpte_tc (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extension_and_user_data (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ff_alternate_horizontal_scan ; 
 int /*<<< orphan*/  ff_alternate_vertical_scan ; 
 int /*<<< orphan*/  ff_init_scantable (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_zigzag_direct ; 
 scalar_t__ get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpeg4_decode_studio_mb ; 
 int /*<<< orphan*/  mpeg4_load_default_matrices (TYPE_2__*) ; 
 int /*<<< orphan*/  next_start_code_studio (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_studio_dc_predictors (TYPE_2__*) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int decode_studio_vop_header(Mpeg4DecContext *ctx, GetBitContext *gb)
{
    MpegEncContext *s = &ctx->m;

    if (get_bits_left(gb) <= 32)
        return 0;

    s->partitioned_frame = 0;
    s->interlaced_dct = 0;
    s->decode_mb = mpeg4_decode_studio_mb;

    decode_smpte_tc(ctx, gb);

    skip_bits(gb, 10); /* temporal_reference */
    skip_bits(gb, 2); /* vop_structure */
    s->pict_type = get_bits(gb, 2) + AV_PICTURE_TYPE_I; /* vop_coding_type */
    if (get_bits1(gb)) { /* vop_coded */
        skip_bits1(gb); /* top_field_first */
        skip_bits1(gb); /* repeat_first_field */
        s->progressive_frame = get_bits1(gb) ^ 1; /* progressive_frame */
    }

    if (s->pict_type == AV_PICTURE_TYPE_I) {
        if (get_bits1(gb))
            reset_studio_dc_predictors(s);
    }

    if (ctx->shape != BIN_ONLY_SHAPE) {
        s->alternate_scan = get_bits1(gb);
        s->frame_pred_frame_dct = get_bits1(gb);
        s->dct_precision = get_bits(gb, 2);
        s->intra_dc_precision = get_bits(gb, 2);
        s->q_scale_type = get_bits1(gb);
    }

    if (s->alternate_scan) {
        ff_init_scantable(s->idsp.idct_permutation, &s->inter_scantable,   ff_alternate_vertical_scan);
        ff_init_scantable(s->idsp.idct_permutation, &s->intra_scantable,   ff_alternate_vertical_scan);
        ff_init_scantable(s->idsp.idct_permutation, &s->intra_h_scantable, ff_alternate_vertical_scan);
        ff_init_scantable(s->idsp.idct_permutation, &s->intra_v_scantable, ff_alternate_vertical_scan);
    } else {
        ff_init_scantable(s->idsp.idct_permutation, &s->inter_scantable,   ff_zigzag_direct);
        ff_init_scantable(s->idsp.idct_permutation, &s->intra_scantable,   ff_zigzag_direct);
        ff_init_scantable(s->idsp.idct_permutation, &s->intra_h_scantable, ff_alternate_horizontal_scan);
        ff_init_scantable(s->idsp.idct_permutation, &s->intra_v_scantable, ff_alternate_vertical_scan);
    }

    mpeg4_load_default_matrices(s);

    next_start_code_studio(gb);
    extension_and_user_data(s, gb, 4);

    return 0;
}