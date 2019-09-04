#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int err_recognition; } ;
struct TYPE_8__ {int type; int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_6__ {int nb_nals; TYPE_3__* nals; } ;
struct TYPE_7__ {TYPE_5__* avctx; TYPE_1__ pkt; } ;
typedef  TYPE_2__ H264Context ;
typedef  TYPE_3__ H2645NAL ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AV_EF_EXPLODE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
#define  H264_NAL_DPA 132 
#define  H264_NAL_IDR_SLICE 131 
#define  H264_NAL_PPS 130 
#define  H264_NAL_SLICE 129 
#define  H264_NAL_SPS 128 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  get_ue_golomb_long (int /*<<< orphan*/ *) ; 
 int init_get_bits8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_last_needed_nal(H264Context *h)
{
    int nals_needed = 0;
    int first_slice = 0;
    int i, ret;

    for (i = 0; i < h->pkt.nb_nals; i++) {
        H2645NAL *nal = &h->pkt.nals[i];
        GetBitContext gb;

        /* packets can sometimes contain multiple PPS/SPS,
         * e.g. two PAFF field pictures in one packet, or a demuxer
         * which splits NALs strangely if so, when frame threading we
         * can't start the next thread until we've read all of them */
        switch (nal->type) {
        case H264_NAL_SPS:
        case H264_NAL_PPS:
            nals_needed = i;
            break;
        case H264_NAL_DPA:
        case H264_NAL_IDR_SLICE:
        case H264_NAL_SLICE:
            ret = init_get_bits8(&gb, nal->data + 1, nal->size - 1);
            if (ret < 0) {
                av_log(h->avctx, AV_LOG_ERROR, "Invalid zero-sized VCL NAL unit\n");
                if (h->avctx->err_recognition & AV_EF_EXPLODE)
                    return ret;

                break;
            }
            if (!get_ue_golomb_long(&gb) ||  // first_mb_in_slice
                !first_slice ||
                first_slice != nal->type)
                nals_needed = i;
            if (!first_slice)
                first_slice = nal->type;
        }
    }

    return nals_needed;
}