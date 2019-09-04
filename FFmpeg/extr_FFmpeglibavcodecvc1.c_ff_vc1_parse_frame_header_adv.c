#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int pict_type; int mb_height; int height; int quarter_sample; int mspel; int mb_stride; size_t mv_table_index; int /*<<< orphan*/  avctx; void* dc_table_index; int /*<<< orphan*/  mbskip_table; TYPE_2__* current_picture_ptr; } ;
struct TYPE_14__ {int numref; int p_frame_skipped; int second_field; int fcm; int field_mode; int fptype; size_t rptfrm; int tff; size_t refdist; int frfd; int bfraction; scalar_t__ brfd; int cur_field_type; int quantizer_mode; int pq; int pqindex; int pquantizer; size_t postproc; int reffield; int* ref_field_type; int mvrange; int dmvrange; size_t lumscale; size_t lumshift; int last_use_ic; size_t mbmodetab; size_t imvtab; size_t icbptab; size_t twomvbptab; size_t fourmvbptab; int range_x; int range_y; int tt_index; void* mv_mode; void* mv_mode2; int intcompfield; int lumscale2; size_t lumshift2; int next_use_ic; int* curr_use_ic; int qs_last; size_t cbptab; int ttmbf; int bi_type; TYPE_3__ s; scalar_t__ dquant; void* y_ac_table_index; void* c_ac_table_index; void* ttfrm; int /*<<< orphan*/  vstransform; int /*<<< orphan*/ * cbpcy_vlc; int /*<<< orphan*/  skip_is_raw; int /*<<< orphan*/  dmb_is_raw; int /*<<< orphan*/  direct_mb_plane; int /*<<< orphan*/ * fourmvbp_vlc; int /*<<< orphan*/ * twomvbp_vlc; int /*<<< orphan*/ * imv_vlc; int /*<<< orphan*/ * mbmode_vlc; void* fourmvswitch; void* intcomp; int /*<<< orphan*/  extended_dmv; int /*<<< orphan*/  fmb_is_raw; int /*<<< orphan*/  forward_mb_plane; int /*<<< orphan*/  k_y; int /*<<< orphan*/  k_x; int /*<<< orphan*/  extended_mv; int /*<<< orphan*/  mv_type_mb_plane; int /*<<< orphan*/  mv_type_is_raw; int /*<<< orphan*/ * last_lutuv; int /*<<< orphan*/ * last_luty; int /*<<< orphan*/ * curr_lutuv; int /*<<< orphan*/ * curr_luty; scalar_t__ interlace; int /*<<< orphan*/  overflg_is_raw; int /*<<< orphan*/  over_flags_plane; void* condover; int /*<<< orphan*/  overlap; int /*<<< orphan*/  acpred_is_raw; int /*<<< orphan*/  acpred_plane; int /*<<< orphan*/  fieldtx_is_raw; int /*<<< orphan*/  fieldtx_plane; scalar_t__ first_pic_header_flag; scalar_t__ parse_only; scalar_t__ postprocflag; scalar_t__ dquantfrm; void* halfpq; void* interpfrm; scalar_t__ finterpflag; int /*<<< orphan*/  refdist_flag; void* uvsamp; void* rnd; scalar_t__ panscanflag; void* rff; scalar_t__ psf; scalar_t__ broadcast; scalar_t__ tfcntrflag; int /*<<< orphan*/  pic_header_flag; } ;
typedef  TYPE_4__ VC1Context ;
struct TYPE_15__ {int /*<<< orphan*/  table; } ;
struct TYPE_12__ {TYPE_1__* f; } ;
struct TYPE_11__ {int pict_type; } ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
#define  AV_PICTURE_TYPE_B 134 
#define  AV_PICTURE_TYPE_BI 133 
#define  AV_PICTURE_TYPE_I 132 
#define  AV_PICTURE_TYPE_P 131 
 void* CONDOVER_NONE ; 
 void* CONDOVER_SELECT ; 
 int FFALIGN (int,int) ; 
 int ILACE_FIELD ; 
 int ILACE_FRAME ; 
 int /*<<< orphan*/  INIT_LUT (size_t,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* MV_PMODE_1MV ; 
 void* MV_PMODE_1MV_HPEL ; 
 void* MV_PMODE_1MV_HPEL_BILIN ; 
 void* MV_PMODE_INTENSITY_COMP ; 
 void* MV_PMODE_MIXED_MV ; 
 int PROGRESSIVE ; 
#define  QUANT_FRAME_EXPLICIT 130 
#define  QUANT_FRAME_IMPLICIT 129 
#define  QUANT_NON_UNIFORM 128 
 void* TT_8X8 ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  avpriv_report_missing_feature (int /*<<< orphan*/ ,char*) ; 
 int bitplane_decoding (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__*) ; 
 void* decode012 (int /*<<< orphan*/ *) ; 
 int decode210 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ff_vc1_1ref_mvdata_vlc ; 
 int /*<<< orphan*/ * ff_vc1_2mv_block_pattern_vlc ; 
 int /*<<< orphan*/ * ff_vc1_2ref_mvdata_vlc ; 
 int /*<<< orphan*/ * ff_vc1_4mv_block_pattern_vlc ; 
 TYPE_9__ ff_vc1_bfraction_vlc ; 
 int /*<<< orphan*/ * ff_vc1_cbpcy_p_vlc ; 
 int /*<<< orphan*/ * ff_vc1_icbpcy_vlc ; 
 int /*<<< orphan*/ * ff_vc1_if_1mv_mbmode_vlc ; 
 int /*<<< orphan*/ * ff_vc1_if_mmv_mbmode_vlc ; 
 int /*<<< orphan*/ * ff_vc1_intfr_4mv_mbmode_vlc ; 
 int /*<<< orphan*/ * ff_vc1_intfr_non4mv_mbmode_vlc ; 
 void*** ff_vc1_mv_pmode_table ; 
 void*** ff_vc1_mv_pmode_table2 ; 
 void*** ff_vc1_pquant_table ; 
 void** ff_vc1_ttfrm_to_tt ; 
 size_t get_bits (int /*<<< orphan*/ *,int) ; 
 void* get_bits1 (int /*<<< orphan*/ *) ; 
 int get_unary (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ read_bfraction (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rotate_luts (TYPE_4__*) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vop_dquant_decoding (TYPE_4__*) ; 

int ff_vc1_parse_frame_header_adv(VC1Context *v, GetBitContext* gb)
{
    int pqindex, lowquant;
    int status;
    int field_mode, fcm;

    v->numref          = 0;
    v->p_frame_skipped = 0;
    if (v->second_field) {
        if (v->fcm != ILACE_FIELD || v->field_mode!=1)
            return -1;
        if (v->fptype & 4)
            v->s.pict_type = (v->fptype & 1) ? AV_PICTURE_TYPE_BI : AV_PICTURE_TYPE_B;
        else
            v->s.pict_type = (v->fptype & 1) ? AV_PICTURE_TYPE_P : AV_PICTURE_TYPE_I;
        v->s.current_picture_ptr->f->pict_type = v->s.pict_type;
        if (!v->pic_header_flag)
            goto parse_common_info;
    }

    field_mode = 0;
    if (v->interlace) {
        fcm = decode012(gb);
        if (fcm) {
            if (fcm == ILACE_FIELD)
                field_mode = 1;
        }
    } else {
        fcm = PROGRESSIVE;
    }
    if (!v->first_pic_header_flag && v->field_mode != field_mode)
        return AVERROR_INVALIDDATA;
    v->field_mode = field_mode;
    v->fcm = fcm;

    av_assert0(    v->s.mb_height == v->s.height + 15 >> 4
                || v->s.mb_height == FFALIGN(v->s.height + 15 >> 4, 2));
    if (v->field_mode) {
        v->s.mb_height = FFALIGN(v->s.height + 15 >> 4, 2);
        v->fptype = get_bits(gb, 3);
        if (v->fptype & 4) // B-picture
            v->s.pict_type = (v->fptype & 2) ? AV_PICTURE_TYPE_BI : AV_PICTURE_TYPE_B;
        else
            v->s.pict_type = (v->fptype & 2) ? AV_PICTURE_TYPE_P : AV_PICTURE_TYPE_I;
    } else {
        v->s.mb_height = v->s.height + 15 >> 4;
        switch (get_unary(gb, 0, 4)) {
        case 0:
            v->s.pict_type = AV_PICTURE_TYPE_P;
            break;
        case 1:
            v->s.pict_type = AV_PICTURE_TYPE_B;
            break;
        case 2:
            v->s.pict_type = AV_PICTURE_TYPE_I;
            break;
        case 3:
            v->s.pict_type = AV_PICTURE_TYPE_BI;
            break;
        case 4:
            v->s.pict_type = AV_PICTURE_TYPE_P; // skipped pic
            v->p_frame_skipped = 1;
            break;
        }
    }
    if (v->tfcntrflag)
        skip_bits(gb, 8);
    if (v->broadcast) {
        if (!v->interlace || v->psf) {
            v->rptfrm = get_bits(gb, 2);
        } else {
            v->tff = get_bits1(gb);
            v->rff = get_bits1(gb);
        }
    } else {
        v->tff = 1;
    }
    if (v->panscanflag) {
        avpriv_report_missing_feature(v->s.avctx, "Pan-scan");
        //...
    }
    if (v->p_frame_skipped) {
        return 0;
    }
    v->rnd = get_bits1(gb);
    if (v->interlace)
        v->uvsamp = get_bits1(gb);
    if(!ff_vc1_bfraction_vlc.table)
        return 0; //parsing only, vlc tables havnt been allocated
    if (v->field_mode) {
        if (!v->refdist_flag)
            v->refdist = 0;
        else if ((v->s.pict_type != AV_PICTURE_TYPE_B) && (v->s.pict_type != AV_PICTURE_TYPE_BI)) {
            v->refdist = get_bits(gb, 2);
            if (v->refdist == 3)
                v->refdist += get_unary(gb, 0, 16);
        }
        if ((v->s.pict_type == AV_PICTURE_TYPE_B) || (v->s.pict_type == AV_PICTURE_TYPE_BI)) {
            if (read_bfraction(v, gb) < 0)
                return AVERROR_INVALIDDATA;
            v->frfd = (v->bfraction * v->refdist) >> 8;
            v->brfd = v->refdist - v->frfd - 1;
            if (v->brfd < 0)
                v->brfd = 0;
        }
        goto parse_common_info;
    }
    if (v->fcm == PROGRESSIVE) {
        if (v->finterpflag)
            v->interpfrm = get_bits1(gb);
        if (v->s.pict_type == AV_PICTURE_TYPE_B) {
            if (read_bfraction(v, gb) < 0)
                return AVERROR_INVALIDDATA;
            if (v->bfraction == 0) {
                v->s.pict_type = AV_PICTURE_TYPE_BI; /* XXX: should not happen here */
            }
        }
    }

    parse_common_info:
    if (v->field_mode)
        v->cur_field_type = !(v->tff ^ v->second_field);
    pqindex = get_bits(gb, 5);
    if (!pqindex)
        return -1;
    if (v->quantizer_mode == QUANT_FRAME_IMPLICIT)
        v->pq = ff_vc1_pquant_table[0][pqindex];
    else
        v->pq = ff_vc1_pquant_table[1][pqindex];
    v->pqindex = pqindex;
    if (pqindex < 9)
        v->halfpq = get_bits1(gb);
    else
        v->halfpq = 0;
    switch (v->quantizer_mode) {
    case QUANT_FRAME_IMPLICIT:
        v->pquantizer = pqindex < 9;
        break;
    case QUANT_NON_UNIFORM:
        v->pquantizer = 0;
        break;
    case QUANT_FRAME_EXPLICIT:
        v->pquantizer = get_bits1(gb);
        break;
    default:
        v->pquantizer = 1;
        break;
    }
    v->dquantfrm = 0;
    if (v->postprocflag)
        v->postproc = get_bits(gb, 2);

    if (v->parse_only)
        return 0;

    if (v->first_pic_header_flag)
        rotate_luts(v);

    switch (v->s.pict_type) {
    case AV_PICTURE_TYPE_I:
    case AV_PICTURE_TYPE_BI:
        if (v->fcm == ILACE_FRAME) { //interlace frame picture
            status = bitplane_decoding(v->fieldtx_plane, &v->fieldtx_is_raw, v);
            if (status < 0)
                return -1;
            av_log(v->s.avctx, AV_LOG_DEBUG, "FIELDTX plane encoding: "
                   "Imode: %i, Invert: %i\n", status>>1, status&1);
        } else
            v->fieldtx_is_raw = 0;
        status = bitplane_decoding(v->acpred_plane, &v->acpred_is_raw, v);
        if (status < 0)
            return -1;
        av_log(v->s.avctx, AV_LOG_DEBUG, "ACPRED plane encoding: "
               "Imode: %i, Invert: %i\n", status>>1, status&1);
        v->condover = CONDOVER_NONE;
        if (v->overlap && v->pq <= 8) {
            v->condover = decode012(gb);
            if (v->condover == CONDOVER_SELECT) {
                status = bitplane_decoding(v->over_flags_plane, &v->overflg_is_raw, v);
                if (status < 0)
                    return -1;
                av_log(v->s.avctx, AV_LOG_DEBUG, "CONDOVER plane encoding: "
                       "Imode: %i, Invert: %i\n", status>>1, status&1);
            }
        }
        break;
    case AV_PICTURE_TYPE_P:
        if (v->field_mode) {
            v->numref = get_bits1(gb);
            if (!v->numref) {
                v->reffield          = get_bits1(gb);
                v->ref_field_type[0] = v->reffield ^ !v->cur_field_type;
            }
        }
        if (v->extended_mv)
            v->mvrange = get_unary(gb, 0, 3);
        else
            v->mvrange = 0;
        if (v->interlace) {
            if (v->extended_dmv)
                v->dmvrange = get_unary(gb, 0, 3);
            else
                v->dmvrange = 0;
            if (v->fcm == ILACE_FRAME) { // interlaced frame picture
                v->fourmvswitch = get_bits1(gb);
                v->intcomp      = get_bits1(gb);
                if (v->intcomp) {
                    v->lumscale = get_bits(gb, 6);
                    v->lumshift = get_bits(gb, 6);
                    INIT_LUT(v->lumscale, v->lumshift, v->last_luty[0], v->last_lutuv[0], 1);
                    INIT_LUT(v->lumscale, v->lumshift, v->last_luty[1], v->last_lutuv[1], 1);
                    v->last_use_ic = 1;
                }
                status = bitplane_decoding(v->s.mbskip_table, &v->skip_is_raw, v);
                if (status < 0)
                    return -1;
                av_log(v->s.avctx, AV_LOG_DEBUG, "SKIPMB plane encoding: "
                       "Imode: %i, Invert: %i\n", status>>1, status&1);
                v->mbmodetab = get_bits(gb, 2);
                if (v->fourmvswitch)
                    v->mbmode_vlc = &ff_vc1_intfr_4mv_mbmode_vlc[v->mbmodetab];
                else
                    v->mbmode_vlc = &ff_vc1_intfr_non4mv_mbmode_vlc[v->mbmodetab];
                v->imvtab      = get_bits(gb, 2);
                v->imv_vlc     = &ff_vc1_1ref_mvdata_vlc[v->imvtab];
                // interlaced p-picture cbpcy range is [1, 63]
                v->icbptab     = get_bits(gb, 3);
                v->cbpcy_vlc   = &ff_vc1_icbpcy_vlc[v->icbptab];
                v->twomvbptab     = get_bits(gb, 2);
                v->twomvbp_vlc = &ff_vc1_2mv_block_pattern_vlc[v->twomvbptab];
                if (v->fourmvswitch) {
                    v->fourmvbptab     = get_bits(gb, 2);
                    v->fourmvbp_vlc = &ff_vc1_4mv_block_pattern_vlc[v->fourmvbptab];
                }
            }
        }
        v->k_x = v->mvrange + 9 + (v->mvrange >> 1); //k_x can be 9 10 12 13
        v->k_y = v->mvrange + 8; //k_y can be 8 9 10 11
        v->range_x = 1 << (v->k_x - 1);
        v->range_y = 1 << (v->k_y - 1);

        v->tt_index = (v->pq > 4) + (v->pq > 12);
        if (v->fcm != ILACE_FRAME) {
            int mvmode;
            mvmode     = get_unary(gb, 1, 4);
            lowquant   = (v->pq > 12) ? 0 : 1;
            v->mv_mode = ff_vc1_mv_pmode_table[lowquant][mvmode];
            if (v->mv_mode == MV_PMODE_INTENSITY_COMP) {
                int mvmode2;
                mvmode2 = get_unary(gb, 1, 3);
                v->mv_mode2 = ff_vc1_mv_pmode_table2[lowquant][mvmode2];
                if (v->field_mode) {
                    v->intcompfield = decode210(gb) ^ 3;
                } else
                    v->intcompfield = 3;

                v->lumscale2 = v->lumscale = 32;
                v->lumshift2 = v->lumshift =  0;
                if (v->intcompfield & 1) {
                    v->lumscale = get_bits(gb, 6);
                    v->lumshift = get_bits(gb, 6);
                }
                if ((v->intcompfield & 2) && v->field_mode) {
                    v->lumscale2 = get_bits(gb, 6);
                    v->lumshift2 = get_bits(gb, 6);
                } else if(!v->field_mode) {
                    v->lumscale2 = v->lumscale;
                    v->lumshift2 = v->lumshift;
                }
                if (v->field_mode && v->second_field) {
                    if (v->cur_field_type) {
                        INIT_LUT(v->lumscale , v->lumshift , v->curr_luty[v->cur_field_type^1], v->curr_lutuv[v->cur_field_type^1], 0);
                        INIT_LUT(v->lumscale2, v->lumshift2, v->last_luty[v->cur_field_type  ], v->last_lutuv[v->cur_field_type  ], 1);
                    } else {
                        INIT_LUT(v->lumscale2, v->lumshift2, v->curr_luty[v->cur_field_type^1], v->curr_lutuv[v->cur_field_type^1], 0);
                        INIT_LUT(v->lumscale , v->lumshift , v->last_luty[v->cur_field_type  ], v->last_lutuv[v->cur_field_type  ], 1);
                    }
                    v->next_use_ic = *v->curr_use_ic = 1;
                } else {
                    INIT_LUT(v->lumscale , v->lumshift , v->last_luty[0], v->last_lutuv[0], 1);
                    INIT_LUT(v->lumscale2, v->lumshift2, v->last_luty[1], v->last_lutuv[1], 1);
                }
                v->last_use_ic = 1;
            }
            v->qs_last = v->s.quarter_sample;
            if (v->mv_mode == MV_PMODE_INTENSITY_COMP) {
                v->s.quarter_sample = (v->mv_mode2 != MV_PMODE_1MV_HPEL &&
                                       v->mv_mode2 != MV_PMODE_1MV_HPEL_BILIN);
                v->s.mspel          = (v->mv_mode2 != MV_PMODE_1MV_HPEL_BILIN);
            } else {
                v->s.quarter_sample = (v->mv_mode != MV_PMODE_1MV_HPEL &&
                                       v->mv_mode != MV_PMODE_1MV_HPEL_BILIN);
                v->s.mspel          = (v->mv_mode != MV_PMODE_1MV_HPEL_BILIN);
            }
        }
        if (v->fcm == PROGRESSIVE) { // progressive
            if ((v->mv_mode == MV_PMODE_INTENSITY_COMP &&
                 v->mv_mode2 == MV_PMODE_MIXED_MV)
                || v->mv_mode == MV_PMODE_MIXED_MV) {
                status = bitplane_decoding(v->mv_type_mb_plane, &v->mv_type_is_raw, v);
                if (status < 0)
                    return -1;
                av_log(v->s.avctx, AV_LOG_DEBUG, "MB MV Type plane encoding: "
                       "Imode: %i, Invert: %i\n", status>>1, status&1);
            } else {
                v->mv_type_is_raw = 0;
                memset(v->mv_type_mb_plane, 0, v->s.mb_stride * v->s.mb_height);
            }
            status = bitplane_decoding(v->s.mbskip_table, &v->skip_is_raw, v);
            if (status < 0)
                return -1;
            av_log(v->s.avctx, AV_LOG_DEBUG, "MB Skip plane encoding: "
                   "Imode: %i, Invert: %i\n", status>>1, status&1);

            /* Hopefully this is correct for P-frames */
            v->s.mv_table_index = get_bits(gb, 2); //but using ff_vc1_ tables
            v->cbptab           = get_bits(gb, 2);
            v->cbpcy_vlc        = &ff_vc1_cbpcy_p_vlc[v->cbptab];
        } else if (v->fcm == ILACE_FRAME) { // frame interlaced
            v->qs_last          = v->s.quarter_sample;
            v->s.quarter_sample = 1;
            v->s.mspel          = 1;
        } else {    // field interlaced
            v->mbmodetab = get_bits(gb, 3);
            v->imvtab = get_bits(gb, 2 + v->numref);
            if (!v->numref)
                v->imv_vlc = &ff_vc1_1ref_mvdata_vlc[v->imvtab];
            else
                v->imv_vlc = &ff_vc1_2ref_mvdata_vlc[v->imvtab];
            v->icbptab = get_bits(gb, 3);
            v->cbpcy_vlc = &ff_vc1_icbpcy_vlc[v->icbptab];
            if ((v->mv_mode == MV_PMODE_INTENSITY_COMP &&
                v->mv_mode2 == MV_PMODE_MIXED_MV) || v->mv_mode == MV_PMODE_MIXED_MV) {
                v->fourmvbptab     = get_bits(gb, 2);
                v->fourmvbp_vlc = &ff_vc1_4mv_block_pattern_vlc[v->fourmvbptab];
                v->mbmode_vlc = &ff_vc1_if_mmv_mbmode_vlc[v->mbmodetab];
            } else {
                v->mbmode_vlc = &ff_vc1_if_1mv_mbmode_vlc[v->mbmodetab];
            }
        }
        if (v->dquant) {
            av_log(v->s.avctx, AV_LOG_DEBUG, "VOP DQuant info\n");
            vop_dquant_decoding(v);
        }

        if (v->vstransform) {
            v->ttmbf = get_bits1(gb);
            if (v->ttmbf) {
                v->ttfrm = ff_vc1_ttfrm_to_tt[get_bits(gb, 2)];
            } else
                v->ttfrm = 0; //FIXME Is that so ?
        } else {
            v->ttmbf = 1;
            v->ttfrm = TT_8X8;
        }
        break;
    case AV_PICTURE_TYPE_B:
        if (v->fcm == ILACE_FRAME) {
            if (read_bfraction(v, gb) < 0)
                return AVERROR_INVALIDDATA;
            if (v->bfraction == 0) {
                return -1;
            }
        }
        if (v->extended_mv)
            v->mvrange = get_unary(gb, 0, 3);
        else
            v->mvrange = 0;
        v->k_x     = v->mvrange + 9 + (v->mvrange >> 1); //k_x can be 9 10 12 13
        v->k_y     = v->mvrange + 8; //k_y can be 8 9 10 11
        v->range_x = 1 << (v->k_x - 1);
        v->range_y = 1 << (v->k_y - 1);

        v->tt_index = (v->pq > 4) + (v->pq > 12);

        if (v->field_mode) {
            int mvmode;
            av_log(v->s.avctx, AV_LOG_DEBUG, "B Fields\n");
            if (v->extended_dmv)
                v->dmvrange = get_unary(gb, 0, 3);
            mvmode = get_unary(gb, 1, 3);
            lowquant = (v->pq > 12) ? 0 : 1;
            v->mv_mode          = ff_vc1_mv_pmode_table2[lowquant][mvmode];
            v->qs_last          = v->s.quarter_sample;
            v->s.quarter_sample = (v->mv_mode == MV_PMODE_1MV || v->mv_mode == MV_PMODE_MIXED_MV);
            v->s.mspel          = (v->mv_mode != MV_PMODE_1MV_HPEL_BILIN);
            status = bitplane_decoding(v->forward_mb_plane, &v->fmb_is_raw, v);
            if (status < 0)
                return -1;
            av_log(v->s.avctx, AV_LOG_DEBUG, "MB Forward Type plane encoding: "
                   "Imode: %i, Invert: %i\n", status>>1, status&1);
            v->mbmodetab = get_bits(gb, 3);
            if (v->mv_mode == MV_PMODE_MIXED_MV)
                v->mbmode_vlc = &ff_vc1_if_mmv_mbmode_vlc[v->mbmodetab];
            else
                v->mbmode_vlc = &ff_vc1_if_1mv_mbmode_vlc[v->mbmodetab];
            v->imvtab     = get_bits(gb, 3);
            v->imv_vlc   = &ff_vc1_2ref_mvdata_vlc[v->imvtab];
            v->icbptab   = get_bits(gb, 3);
            v->cbpcy_vlc = &ff_vc1_icbpcy_vlc[v->icbptab];
            if (v->mv_mode == MV_PMODE_MIXED_MV) {
                v->fourmvbptab     = get_bits(gb, 2);
                v->fourmvbp_vlc = &ff_vc1_4mv_block_pattern_vlc[v->fourmvbptab];
            }
            v->numref = 1; // interlaced field B pictures are always 2-ref
        } else if (v->fcm == ILACE_FRAME) {
            if (v->extended_dmv)
                v->dmvrange = get_unary(gb, 0, 3);
            if (get_bits1(gb)) /* intcomp - present but shall always be 0 */
                av_log(v->s.avctx, AV_LOG_WARNING, "Intensity compensation set for B picture\n");
            v->intcomp          = 0;
            v->mv_mode          = MV_PMODE_1MV;
            v->fourmvswitch     = 0;
            v->qs_last          = v->s.quarter_sample;
            v->s.quarter_sample = 1;
            v->s.mspel          = 1;
            status              = bitplane_decoding(v->direct_mb_plane, &v->dmb_is_raw, v);
            if (status < 0)
                return -1;
            av_log(v->s.avctx, AV_LOG_DEBUG, "MB Direct Type plane encoding: "
                   "Imode: %i, Invert: %i\n", status>>1, status&1);
            status = bitplane_decoding(v->s.mbskip_table, &v->skip_is_raw, v);
            if (status < 0)
                return -1;
            av_log(v->s.avctx, AV_LOG_DEBUG, "MB Skip plane encoding: "
                   "Imode: %i, Invert: %i\n", status>>1, status&1);
            v->mbmodetab       = get_bits(gb, 2);
            v->mbmode_vlc   = &ff_vc1_intfr_non4mv_mbmode_vlc[v->mbmodetab];
            v->imvtab       = get_bits(gb, 2);
            v->imv_vlc      = &ff_vc1_1ref_mvdata_vlc[v->imvtab];
            // interlaced p/b-picture cbpcy range is [1, 63]
            v->icbptab      = get_bits(gb, 3);
            v->cbpcy_vlc    = &ff_vc1_icbpcy_vlc[v->icbptab];
            v->twomvbptab      = get_bits(gb, 2);
            v->twomvbp_vlc  = &ff_vc1_2mv_block_pattern_vlc[v->twomvbptab];
            v->fourmvbptab     = get_bits(gb, 2);
            v->fourmvbp_vlc = &ff_vc1_4mv_block_pattern_vlc[v->fourmvbptab];
        } else {
            v->mv_mode          = get_bits1(gb) ? MV_PMODE_1MV : MV_PMODE_1MV_HPEL_BILIN;
            v->qs_last          = v->s.quarter_sample;
            v->s.quarter_sample = (v->mv_mode == MV_PMODE_1MV);
            v->s.mspel          = v->s.quarter_sample;
            status              = bitplane_decoding(v->direct_mb_plane, &v->dmb_is_raw, v);
            if (status < 0)
                return -1;
            av_log(v->s.avctx, AV_LOG_DEBUG, "MB Direct Type plane encoding: "
                   "Imode: %i, Invert: %i\n", status>>1, status&1);
            status = bitplane_decoding(v->s.mbskip_table, &v->skip_is_raw, v);
            if (status < 0)
                return -1;
            av_log(v->s.avctx, AV_LOG_DEBUG, "MB Skip plane encoding: "
                   "Imode: %i, Invert: %i\n", status>>1, status&1);
            v->s.mv_table_index = get_bits(gb, 2);
            v->cbptab = get_bits(gb, 2);
            v->cbpcy_vlc = &ff_vc1_cbpcy_p_vlc[v->cbptab];
        }

        if (v->dquant) {
            av_log(v->s.avctx, AV_LOG_DEBUG, "VOP DQuant info\n");
            vop_dquant_decoding(v);
        }

        if (v->vstransform) {
            v->ttmbf = get_bits1(gb);
            if (v->ttmbf) {
                v->ttfrm = ff_vc1_ttfrm_to_tt[get_bits(gb, 2)];
            } else
                v->ttfrm = 0;
        } else {
            v->ttmbf = 1;
            v->ttfrm = TT_8X8;
        }
        break;
    }

    if (v->fcm != PROGRESSIVE && !v->s.quarter_sample) {
        v->range_x <<= 1;
        v->range_y <<= 1;
    }

    /* AC Syntax */
    v->c_ac_table_index = decode012(gb);
    if (v->s.pict_type == AV_PICTURE_TYPE_I || v->s.pict_type == AV_PICTURE_TYPE_BI) {
        v->y_ac_table_index = decode012(gb);
    }
    /* DC Syntax */
    v->s.dc_table_index = get_bits1(gb);
    if ((v->s.pict_type == AV_PICTURE_TYPE_I || v->s.pict_type == AV_PICTURE_TYPE_BI)
        && v->dquant) {
        av_log(v->s.avctx, AV_LOG_DEBUG, "VOP DQuant info\n");
        vop_dquant_decoding(v);
    }

    v->bi_type = (v->s.pict_type == AV_PICTURE_TYPE_BI);
    if (v->bi_type)
        v->s.pict_type = AV_PICTURE_TYPE_B;

    return 0;
}