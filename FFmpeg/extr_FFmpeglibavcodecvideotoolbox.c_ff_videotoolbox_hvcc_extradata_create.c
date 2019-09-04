#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_12__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_22__ {int min_spatial_segmentation_idc; } ;
typedef  TYPE_6__ VUI ;
struct TYPE_25__ {int data_size; int chroma_format_idc; int bit_depth; int bit_depth_chroma; int max_sub_layers; int temporal_id_nesting_flag; int /*<<< orphan*/  data; TYPE_6__ vui; } ;
struct TYPE_23__ {int profile_space; int tier_flag; int profile_idc; int progressive_source_flag; int interlaced_source_flag; int non_packed_constraint_flag; int frame_only_constraint_flag; int level_idc; int /*<<< orphan*/  profile_compatibility_flag; } ;
struct TYPE_17__ {TYPE_7__ general_ptl; } ;
struct TYPE_24__ {int data_size; int /*<<< orphan*/  data; TYPE_1__ ptl; } ;
struct TYPE_21__ {TYPE_4__** pps_list; TYPE_3__** sps_list; TYPE_2__** vps_list; TYPE_10__* pps; TYPE_9__* sps; TYPE_8__* vps; } ;
struct TYPE_20__ {scalar_t__ data; } ;
struct TYPE_19__ {scalar_t__ data; } ;
struct TYPE_18__ {scalar_t__ data; } ;
struct TYPE_16__ {TYPE_11__* priv_data; } ;
struct TYPE_15__ {TYPE_5__ ps; } ;
struct TYPE_14__ {int data_size; int /*<<< orphan*/  data; scalar_t__ tiles_enabled_flag; scalar_t__ entropy_coding_sync_enabled_flag; } ;
typedef  TYPE_7__ PTLCommon ;
typedef  TYPE_8__ HEVCVPS ;
typedef  TYPE_9__ HEVCSPS ;
typedef  TYPE_10__ HEVCPPS ;
typedef  TYPE_11__ HEVCContext ;
typedef  int /*<<< orphan*/ * CFDataRef ;
typedef  TYPE_12__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_W8 (int*,int) ; 
 int /*<<< orphan*/  AV_WB16 (int*,int) ; 
 int /*<<< orphan*/  AV_WN32 (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CFDataCreate (int /*<<< orphan*/ ,int*,int) ; 
 int HEVC_MAX_PPS_COUNT ; 
 int HEVC_MAX_SPS_COUNT ; 
 int HEVC_MAX_VPS_COUNT ; 
 int HEVC_NAL_PPS ; 
 int HEVC_NAL_SPS ; 
 int HEVC_NAL_VPS ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_free (int*) ; 
 int* av_malloc (int) ; 
 int /*<<< orphan*/  kCFAllocatorDefault ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 

CFDataRef ff_videotoolbox_hvcc_extradata_create(AVCodecContext *avctx)
{
    HEVCContext *h = avctx->priv_data;
    int i, num_vps = 0, num_sps = 0, num_pps = 0;
    const HEVCVPS *vps = h->ps.vps;
    const HEVCSPS *sps = h->ps.sps;
    const HEVCPPS *pps = h->ps.pps;
    PTLCommon ptlc = vps->ptl.general_ptl;
    VUI vui = sps->vui;
    uint8_t parallelismType;
    CFDataRef data = NULL;
    uint8_t *p;
    int vt_extradata_size = 23 + 3 + 3 + 3;
    uint8_t *vt_extradata;

#define COUNT_SIZE_PS(T, t) \
    for (i = 0; i < HEVC_MAX_##T##PS_COUNT; i++) { \
        if (h->ps.t##ps_list[i]) { \
            const HEVC##T##PS *lps = (const HEVC##T##PS *)h->ps.t##ps_list[i]->data; \
            vt_extradata_size += 2 + lps->data_size; \
            num_##t##ps++; \
        } \
    }

    COUNT_SIZE_PS(V, v)
    COUNT_SIZE_PS(S, s)
    COUNT_SIZE_PS(P, p)

    vt_extradata = av_malloc(vt_extradata_size);
    if (!vt_extradata)
        return NULL;
    p = vt_extradata;

    /* unsigned int(8) configurationVersion = 1; */
    AV_W8(p + 0, 1);

    /*
     * unsigned int(2) general_profile_space;
     * unsigned int(1) general_tier_flag;
     * unsigned int(5) general_profile_idc;
     */
    AV_W8(p + 1, ptlc.profile_space << 6 |
                 ptlc.tier_flag     << 5 |
                 ptlc.profile_idc);

    /* unsigned int(32) general_profile_compatibility_flags; */
    memcpy(p + 2, ptlc.profile_compatibility_flag, 4);

    /* unsigned int(48) general_constraint_indicator_flags; */
    AV_W8(p + 6, ptlc.progressive_source_flag    << 7 |
                 ptlc.interlaced_source_flag     << 6 |
                 ptlc.non_packed_constraint_flag << 5 |
                 ptlc.frame_only_constraint_flag << 4);
    AV_W8(p + 7, 0);
    AV_WN32(p + 8, 0);

    /* unsigned int(8) general_level_idc; */
    AV_W8(p + 12, ptlc.level_idc);

    /*
     * bit(4) reserved = ‘1111’b;
     * unsigned int(12) min_spatial_segmentation_idc;
     */
    AV_W8(p + 13, 0xf0 | (vui.min_spatial_segmentation_idc >> 4));
    AV_W8(p + 14, vui.min_spatial_segmentation_idc & 0xff);

    /*
     * bit(6) reserved = ‘111111’b;
     * unsigned int(2) parallelismType;
     */
    if (!vui.min_spatial_segmentation_idc)
        parallelismType = 0;
    else if (pps->entropy_coding_sync_enabled_flag && pps->tiles_enabled_flag)
        parallelismType = 0;
    else if (pps->entropy_coding_sync_enabled_flag)
        parallelismType = 3;
    else if (pps->tiles_enabled_flag)
        parallelismType = 2;
    else
        parallelismType = 1;
    AV_W8(p + 15, 0xfc | parallelismType);

    /*
     * bit(6) reserved = ‘111111’b;
     * unsigned int(2) chromaFormat;
     */
    AV_W8(p + 16, sps->chroma_format_idc | 0xfc);

    /*
     * bit(5) reserved = ‘11111’b;
     * unsigned int(3) bitDepthLumaMinus8;
     */
    AV_W8(p + 17, (sps->bit_depth - 8) | 0xfc);

    /*
     * bit(5) reserved = ‘11111’b;
     * unsigned int(3) bitDepthChromaMinus8;
     */
    AV_W8(p + 18, (sps->bit_depth_chroma - 8) | 0xfc);

    /* bit(16) avgFrameRate; */
    AV_WB16(p + 19, 0);

    /*
     * bit(2) constantFrameRate;
     * bit(3) numTemporalLayers;
     * bit(1) temporalIdNested;
     * unsigned int(2) lengthSizeMinusOne;
     */
    AV_W8(p + 21, 0                             << 6 |
                  sps->max_sub_layers           << 3 |
                  sps->temporal_id_nesting_flag << 2 |
                  3);

    /* unsigned int(8) numOfArrays; */
    AV_W8(p + 22, 3);

    p += 23;

#define APPEND_PS(T, t) \
    /* \
     * bit(1) array_completeness; \
     * unsigned int(1) reserved = 0; \
     * unsigned int(6) NAL_unit_type; \
     */ \
    AV_W8(p, 1 << 7 | \
             HEVC_NAL_##T##PS & 0x3f); \
    /* unsigned int(16) numNalus; */ \
    AV_WB16(p + 1, num_##t##ps); \
    p += 3; \
    for (i = 0; i < HEVC_MAX_##T##PS_COUNT; i++) { \
        if (h->ps.t##ps_list[i]) { \
            const HEVC##T##PS *lps = (const HEVC##T##PS *)h->ps.t##ps_list[i]->data; \
            /* unsigned int(16) nalUnitLength; */ \
            AV_WB16(p, lps->data_size); \
            /* bit(8*nalUnitLength) nalUnit; */ \
            memcpy(p + 2, lps->data, lps->data_size); \
            p += 2 + lps->data_size; \
        } \
    }

    APPEND_PS(V, v)
    APPEND_PS(S, s)
    APPEND_PS(P, p)

    av_assert0(p - vt_extradata == vt_extradata_size);

    data = CFDataCreate(kCFAllocatorDefault, vt_extradata, vt_extradata_size);
    av_free(vt_extradata);
    return data;
}