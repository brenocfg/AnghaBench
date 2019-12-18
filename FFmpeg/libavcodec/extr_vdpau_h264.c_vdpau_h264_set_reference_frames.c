#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_3__* referenceFrames; } ;
struct TYPE_13__ {TYPE_4__ h264; } ;
struct vdpau_picture_context {TYPE_2__ info; } ;
typedef  scalar_t__ VdpVideoSurface ;
struct TYPE_14__ {scalar_t__ surface; scalar_t__ is_long_term; int frame_idx; int /*<<< orphan*/  bottom_is_reference; int /*<<< orphan*/  top_is_reference; } ;
typedef  TYPE_3__ VdpReferenceFrameH264 ;
typedef  TYPE_4__ VdpPictureInfoH264 ;
struct TYPE_18__ {TYPE_6__* priv_data; } ;
struct TYPE_17__ {int short_ref_count; TYPE_5__** short_ref; TYPE_5__** long_ref; TYPE_1__* cur_pic_ptr; } ;
struct TYPE_16__ {int reference; scalar_t__ long_ref; int pic_id; int frame_num; int /*<<< orphan*/  f; } ;
struct TYPE_12__ {struct vdpau_picture_context* hwaccel_picture_private; } ;
typedef  TYPE_5__ H264Picture ;
typedef  TYPE_6__ H264Context ;
typedef  TYPE_7__ AVCodecContext ;

/* Variables and functions */
 size_t H264_RF_COUNT ; 
 int PICT_BOTTOM_FIELD ; 
 int PICT_TOP_FIELD ; 
 int /*<<< orphan*/  VDP_FALSE ; 
 int /*<<< orphan*/  VDP_TRUE ; 
 scalar_t__ ff_vdpau_get_surface_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdpau_h264_clear_rf (TYPE_3__*) ; 
 int /*<<< orphan*/  vdpau_h264_set_rf (TYPE_3__*,TYPE_5__*,int) ; 

__attribute__((used)) static void vdpau_h264_set_reference_frames(AVCodecContext *avctx)
{
    H264Context * const h = avctx->priv_data;
    struct vdpau_picture_context *pic_ctx = h->cur_pic_ptr->hwaccel_picture_private;
    VdpPictureInfoH264 *info = &pic_ctx->info.h264;
    int list;

    VdpReferenceFrameH264 *rf = &info->referenceFrames[0];
#define H264_RF_COUNT FF_ARRAY_ELEMS(info->referenceFrames)

    for (list = 0; list < 2; ++list) {
        H264Picture **lp = list ? h->long_ref : h->short_ref;
        int i, ls    = list ? 16          : h->short_ref_count;

        for (i = 0; i < ls; ++i) {
            H264Picture *pic = lp[i];
            VdpReferenceFrameH264 *rf2;
            VdpVideoSurface surface_ref;
            int pic_frame_idx;

            if (!pic || !pic->reference)
                continue;
            pic_frame_idx = pic->long_ref ? pic->pic_id : pic->frame_num;
            surface_ref = ff_vdpau_get_surface_id(pic->f);

            rf2 = &info->referenceFrames[0];
            while (rf2 != rf) {
                if ((rf2->surface      == surface_ref)   &&
                    (rf2->is_long_term == pic->long_ref) &&
                    (rf2->frame_idx    == pic_frame_idx))
                    break;
                ++rf2;
            }
            if (rf2 != rf) {
                rf2->top_is_reference    |= (pic->reference & PICT_TOP_FIELD)    ? VDP_TRUE : VDP_FALSE;
                rf2->bottom_is_reference |= (pic->reference & PICT_BOTTOM_FIELD) ? VDP_TRUE : VDP_FALSE;
                continue;
            }

            if (rf >= &info->referenceFrames[H264_RF_COUNT])
                continue;

            vdpau_h264_set_rf(rf, pic, pic->reference);
            ++rf;
        }
    }

    for (; rf < &info->referenceFrames[H264_RF_COUNT]; ++rf)
        vdpau_h264_clear_rf(rf);
}