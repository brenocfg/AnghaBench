#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_1__ ;

/* Type definitions */
struct TYPE_30__ {int /*<<< orphan*/  log_ctx; } ;
struct TYPE_29__ {int data_size; int type; TYPE_1__* content; int /*<<< orphan*/ * data; int /*<<< orphan*/  data_ref; } ;
struct TYPE_28__ {int data_size; int data_bit_start; int /*<<< orphan*/  data; int /*<<< orphan*/  data_ref; int /*<<< orphan*/  header; } ;
typedef  TYPE_1__ H265RawVPS ;
typedef  TYPE_1__ H265RawSlice ;
typedef  TYPE_1__ H265RawSPS ;
typedef  int /*<<< orphan*/  H265RawSEI ;
typedef  TYPE_1__ H265RawPPS ;
typedef  int /*<<< orphan*/  H265RawAUD ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_5__ CodedBitstreamUnit ;
typedef  TYPE_6__ CodedBitstreamContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENOSYS ; 
#define  HEVC_NAL_AUD 149 
#define  HEVC_NAL_BLA_N_LP 148 
#define  HEVC_NAL_BLA_W_LP 147 
#define  HEVC_NAL_BLA_W_RADL 146 
#define  HEVC_NAL_CRA_NUT 145 
#define  HEVC_NAL_IDR_N_LP 144 
#define  HEVC_NAL_IDR_W_RADL 143 
#define  HEVC_NAL_PPS 142 
#define  HEVC_NAL_RADL_N 141 
#define  HEVC_NAL_RADL_R 140 
#define  HEVC_NAL_RASL_N 139 
#define  HEVC_NAL_RASL_R 138 
#define  HEVC_NAL_SEI_PREFIX 137 
#define  HEVC_NAL_SEI_SUFFIX 136 
#define  HEVC_NAL_SPS 135 
#define  HEVC_NAL_STSA_N 134 
#define  HEVC_NAL_STSA_R 133 
#define  HEVC_NAL_TRAIL_N 132 
#define  HEVC_NAL_TRAIL_R 131 
#define  HEVC_NAL_TSA_N 130 
#define  HEVC_NAL_TSA_R 129 
#define  HEVC_NAL_VPS 128 
 int /*<<< orphan*/  av_buffer_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  cbs_h265_free_pps ; 
 int /*<<< orphan*/  cbs_h265_free_sei ; 
 int /*<<< orphan*/  cbs_h265_free_slice ; 
 int /*<<< orphan*/  cbs_h265_free_sps ; 
 int /*<<< orphan*/  cbs_h265_free_vps ; 
 int cbs_h265_read_aud (TYPE_6__*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int cbs_h265_read_pps (TYPE_6__*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int cbs_h265_read_sei (TYPE_6__*,int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int cbs_h265_read_slice_segment_header (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int cbs_h265_read_sps (TYPE_6__*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int cbs_h265_read_vps (TYPE_6__*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int cbs_h265_replace_pps (TYPE_6__*,TYPE_5__*) ; 
 int cbs_h265_replace_sps (TYPE_6__*,TYPE_5__*) ; 
 int cbs_h265_replace_vps (TYPE_6__*,TYPE_5__*) ; 
 int ff_cbs_alloc_unit_content (TYPE_6__*,TYPE_5__*,int,int /*<<< orphan*/ *) ; 
 int get_bits_count (int /*<<< orphan*/ *) ; 
 int init_get_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int cbs_h265_read_nal_unit(CodedBitstreamContext *ctx,
                                  CodedBitstreamUnit *unit)
{
    GetBitContext gbc;
    int err;

    err = init_get_bits(&gbc, unit->data, 8 * unit->data_size);
    if (err < 0)
        return err;

    switch (unit->type) {
    case HEVC_NAL_VPS:
        {
            H265RawVPS *vps;

            err = ff_cbs_alloc_unit_content(ctx, unit, sizeof(*vps),
                                            &cbs_h265_free_vps);
            if (err < 0)
                return err;
            vps = unit->content;

            err = cbs_h265_read_vps(ctx, &gbc, vps);
            if (err < 0)
                return err;

            err = cbs_h265_replace_vps(ctx, unit);
            if (err < 0)
                return err;
        }
        break;
    case HEVC_NAL_SPS:
        {
            H265RawSPS *sps;

            err = ff_cbs_alloc_unit_content(ctx, unit, sizeof(*sps),
                                            &cbs_h265_free_sps);
            if (err < 0)
                return err;
            sps = unit->content;

            err = cbs_h265_read_sps(ctx, &gbc, sps);
            if (err < 0)
                return err;

            err = cbs_h265_replace_sps(ctx, unit);
            if (err < 0)
                return err;
        }
        break;

    case HEVC_NAL_PPS:
        {
            H265RawPPS *pps;

            err = ff_cbs_alloc_unit_content(ctx, unit, sizeof(*pps),
                                            &cbs_h265_free_pps);
            if (err < 0)
                return err;
            pps = unit->content;

            err = cbs_h265_read_pps(ctx, &gbc, pps);
            if (err < 0)
                return err;

            err = cbs_h265_replace_pps(ctx, unit);
            if (err < 0)
                return err;
        }
        break;

    case HEVC_NAL_TRAIL_N:
    case HEVC_NAL_TRAIL_R:
    case HEVC_NAL_TSA_N:
    case HEVC_NAL_TSA_R:
    case HEVC_NAL_STSA_N:
    case HEVC_NAL_STSA_R:
    case HEVC_NAL_RADL_N:
    case HEVC_NAL_RADL_R:
    case HEVC_NAL_RASL_N:
    case HEVC_NAL_RASL_R:
    case HEVC_NAL_BLA_W_LP:
    case HEVC_NAL_BLA_W_RADL:
    case HEVC_NAL_BLA_N_LP:
    case HEVC_NAL_IDR_W_RADL:
    case HEVC_NAL_IDR_N_LP:
    case HEVC_NAL_CRA_NUT:
        {
            H265RawSlice *slice;
            int pos, len;

            err = ff_cbs_alloc_unit_content(ctx, unit, sizeof(*slice),
                                            &cbs_h265_free_slice);
            if (err < 0)
                return err;
            slice = unit->content;

            err = cbs_h265_read_slice_segment_header(ctx, &gbc, &slice->header);
            if (err < 0)
                return err;

            pos = get_bits_count(&gbc);
            len = unit->data_size;
            if (!unit->data[len - 1]) {
                int z;
                for (z = 0; z < len && !unit->data[len - z - 1]; z++);
                av_log(ctx->log_ctx, AV_LOG_DEBUG, "Deleted %d trailing zeroes "
                       "from slice data.\n", z);
                len -= z;
            }

            slice->data_size = len - pos / 8;
            slice->data_ref  = av_buffer_ref(unit->data_ref);
            if (!slice->data_ref)
                return AVERROR(ENOMEM);
            slice->data = unit->data + pos / 8;
            slice->data_bit_start = pos % 8;
        }
        break;

    case HEVC_NAL_AUD:
        {
            err = ff_cbs_alloc_unit_content(ctx, unit,
                                            sizeof(H265RawAUD), NULL);
            if (err < 0)
                return err;

            err = cbs_h265_read_aud(ctx, &gbc, unit->content);
            if (err < 0)
                return err;
        }
        break;

    case HEVC_NAL_SEI_PREFIX:
    case HEVC_NAL_SEI_SUFFIX:
        {
            err = ff_cbs_alloc_unit_content(ctx, unit, sizeof(H265RawSEI),
                                            &cbs_h265_free_sei);

            if (err < 0)
                return err;

            err = cbs_h265_read_sei(ctx, &gbc, unit->content,
                                    unit->type == HEVC_NAL_SEI_PREFIX);

            if (err < 0)
                return err;
        }
        break;

    default:
        return AVERROR(ENOSYS);
    }

    return 0;
}