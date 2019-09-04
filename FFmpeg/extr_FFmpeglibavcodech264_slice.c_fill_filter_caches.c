#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_15__ {TYPE_2__* pps; } ;
struct TYPE_13__ {int* mb_type; int* qscale_table; } ;
struct TYPE_17__ {int const mb_stride; int* slice_table; int** non_zero_count; int* cbp_table; TYPE_3__ ps; TYPE_1__ cur_pic; } ;
struct TYPE_16__ {int mb_xy; int mb_y; int top_mb_xy; int* left_mb_xy; int qp_thresh; int deblocking_filter; int slice_num; int top_type; int* left_type; int list_count; int* non_zero_count_cache; int cbp; } ;
struct TYPE_14__ {scalar_t__ transform_8x8_mode; } ;
typedef  TYPE_4__ H264SliceContext ;
typedef  TYPE_5__ H264Context ;

/* Variables and functions */
 int /*<<< orphan*/  AV_COPY32 (int*,int*) ; 
 int /*<<< orphan*/  CABAC (TYPE_5__ const*) ; 
 scalar_t__ FRAME_MBAFF (TYPE_5__ const*) ; 
 scalar_t__ IS_8x8DCT (int) ; 
 int IS_INTERLACED (int) ; 
 scalar_t__ IS_INTRA (int) ; 
 size_t LBOT ; 
 int LEFT_MBS ; 
 size_t LTOP ; 
 int const MB_FIELD (TYPE_4__*) ; 
 int /*<<< orphan*/  fill_filter_caches_inter (TYPE_5__ const*,TYPE_4__*,int,int,int*,int,int*,int const,int) ; 
 size_t* scan8 ; 

__attribute__((used)) static int fill_filter_caches(const H264Context *h, H264SliceContext *sl, int mb_type)
{
    const int mb_xy = sl->mb_xy;
    int top_xy, left_xy[LEFT_MBS];
    int top_type, left_type[LEFT_MBS];
    uint8_t *nnz;
    uint8_t *nnz_cache;

    top_xy = mb_xy - (h->mb_stride << MB_FIELD(sl));

    left_xy[LBOT] = left_xy[LTOP] = mb_xy - 1;
    if (FRAME_MBAFF(h)) {
        const int left_mb_field_flag = IS_INTERLACED(h->cur_pic.mb_type[mb_xy - 1]);
        const int curr_mb_field_flag = IS_INTERLACED(mb_type);
        if (sl->mb_y & 1) {
            if (left_mb_field_flag != curr_mb_field_flag)
                left_xy[LTOP] -= h->mb_stride;
        } else {
            if (curr_mb_field_flag)
                top_xy += h->mb_stride &
                          (((h->cur_pic.mb_type[top_xy] >> 7) & 1) - 1);
            if (left_mb_field_flag != curr_mb_field_flag)
                left_xy[LBOT] += h->mb_stride;
        }
    }

    sl->top_mb_xy        = top_xy;
    sl->left_mb_xy[LTOP] = left_xy[LTOP];
    sl->left_mb_xy[LBOT] = left_xy[LBOT];
    {
        /* For sufficiently low qp, filtering wouldn't do anything.
         * This is a conservative estimate: could also check beta_offset
         * and more accurate chroma_qp. */
        int qp_thresh = sl->qp_thresh; // FIXME strictly we should store qp_thresh for each mb of a slice
        int qp        = h->cur_pic.qscale_table[mb_xy];
        if (qp <= qp_thresh &&
            (left_xy[LTOP] < 0 ||
             ((qp + h->cur_pic.qscale_table[left_xy[LTOP]] + 1) >> 1) <= qp_thresh) &&
            (top_xy < 0 ||
             ((qp + h->cur_pic.qscale_table[top_xy] + 1) >> 1) <= qp_thresh)) {
            if (!FRAME_MBAFF(h))
                return 1;
            if ((left_xy[LTOP] < 0 ||
                 ((qp + h->cur_pic.qscale_table[left_xy[LBOT]] + 1) >> 1) <= qp_thresh) &&
                (top_xy < h->mb_stride ||
                 ((qp + h->cur_pic.qscale_table[top_xy - h->mb_stride] + 1) >> 1) <= qp_thresh))
                return 1;
        }
    }

    top_type        = h->cur_pic.mb_type[top_xy];
    left_type[LTOP] = h->cur_pic.mb_type[left_xy[LTOP]];
    left_type[LBOT] = h->cur_pic.mb_type[left_xy[LBOT]];
    if (sl->deblocking_filter == 2) {
        if (h->slice_table[top_xy] != sl->slice_num)
            top_type = 0;
        if (h->slice_table[left_xy[LBOT]] != sl->slice_num)
            left_type[LTOP] = left_type[LBOT] = 0;
    } else {
        if (h->slice_table[top_xy] == 0xFFFF)
            top_type = 0;
        if (h->slice_table[left_xy[LBOT]] == 0xFFFF)
            left_type[LTOP] = left_type[LBOT] = 0;
    }
    sl->top_type        = top_type;
    sl->left_type[LTOP] = left_type[LTOP];
    sl->left_type[LBOT] = left_type[LBOT];

    if (IS_INTRA(mb_type))
        return 0;

    fill_filter_caches_inter(h, sl, mb_type, top_xy, left_xy,
                             top_type, left_type, mb_xy, 0);
    if (sl->list_count == 2)
        fill_filter_caches_inter(h, sl, mb_type, top_xy, left_xy,
                                 top_type, left_type, mb_xy, 1);

    nnz       = h->non_zero_count[mb_xy];
    nnz_cache = sl->non_zero_count_cache;
    AV_COPY32(&nnz_cache[4 + 8 * 1], &nnz[0]);
    AV_COPY32(&nnz_cache[4 + 8 * 2], &nnz[4]);
    AV_COPY32(&nnz_cache[4 + 8 * 3], &nnz[8]);
    AV_COPY32(&nnz_cache[4 + 8 * 4], &nnz[12]);
    sl->cbp = h->cbp_table[mb_xy];

    if (top_type) {
        nnz = h->non_zero_count[top_xy];
        AV_COPY32(&nnz_cache[4 + 8 * 0], &nnz[3 * 4]);
    }

    if (left_type[LTOP]) {
        nnz = h->non_zero_count[left_xy[LTOP]];
        nnz_cache[3 + 8 * 1] = nnz[3 + 0 * 4];
        nnz_cache[3 + 8 * 2] = nnz[3 + 1 * 4];
        nnz_cache[3 + 8 * 3] = nnz[3 + 2 * 4];
        nnz_cache[3 + 8 * 4] = nnz[3 + 3 * 4];
    }

    /* CAVLC 8x8dct requires NNZ values for residual decoding that differ
     * from what the loop filter needs */
    if (!CABAC(h) && h->ps.pps->transform_8x8_mode) {
        if (IS_8x8DCT(top_type)) {
            nnz_cache[4 + 8 * 0] =
            nnz_cache[5 + 8 * 0] = (h->cbp_table[top_xy] & 0x4000) >> 12;
            nnz_cache[6 + 8 * 0] =
            nnz_cache[7 + 8 * 0] = (h->cbp_table[top_xy] & 0x8000) >> 12;
        }
        if (IS_8x8DCT(left_type[LTOP])) {
            nnz_cache[3 + 8 * 1] =
            nnz_cache[3 + 8 * 2] = (h->cbp_table[left_xy[LTOP]] & 0x2000) >> 12; // FIXME check MBAFF
        }
        if (IS_8x8DCT(left_type[LBOT])) {
            nnz_cache[3 + 8 * 3] =
            nnz_cache[3 + 8 * 4] = (h->cbp_table[left_xy[LBOT]] & 0x8000) >> 12; // FIXME check MBAFF
        }

        if (IS_8x8DCT(mb_type)) {
            nnz_cache[scan8[0]] =
            nnz_cache[scan8[1]] =
            nnz_cache[scan8[2]] =
            nnz_cache[scan8[3]] = (sl->cbp & 0x1000) >> 12;

            nnz_cache[scan8[0 + 4]] =
            nnz_cache[scan8[1 + 4]] =
            nnz_cache[scan8[2 + 4]] =
            nnz_cache[scan8[3 + 4]] = (sl->cbp & 0x2000) >> 12;

            nnz_cache[scan8[0 + 8]] =
            nnz_cache[scan8[1 + 8]] =
            nnz_cache[scan8[2 + 8]] =
            nnz_cache[scan8[3 + 8]] = (sl->cbp & 0x4000) >> 12;

            nnz_cache[scan8[0 + 12]] =
            nnz_cache[scan8[1 + 12]] =
            nnz_cache[scan8[2 + 12]] =
            nnz_cache[scan8[3 + 12]] = (sl->cbp & 0x8000) >> 12;
        }
    }

    return 0;
}