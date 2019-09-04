#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int nb_side_data; scalar_t__ width; scalar_t__ height; int /*<<< orphan*/ * private_ref; int /*<<< orphan*/ * opaque_ref; TYPE_1__** side_data; int /*<<< orphan*/  metadata; int /*<<< orphan*/  chroma_location; int /*<<< orphan*/  color_range; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  color_trc; int /*<<< orphan*/  color_primaries; int /*<<< orphan*/  decode_error_flags; int /*<<< orphan*/  flags; int /*<<< orphan*/  display_picture_number; int /*<<< orphan*/  coded_picture_number; int /*<<< orphan*/  best_effort_timestamp; int /*<<< orphan*/  quality; int /*<<< orphan*/  reordered_opaque; int /*<<< orphan*/  pkt_duration; int /*<<< orphan*/  pkt_size; int /*<<< orphan*/  pkt_pos; int /*<<< orphan*/  pkt_dts; int /*<<< orphan*/  opaque; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  palette_has_changed; int /*<<< orphan*/  top_field_first; int /*<<< orphan*/  interlaced_frame; int /*<<< orphan*/  repeat_pict; int /*<<< orphan*/  pts; int /*<<< orphan*/  crop_right; int /*<<< orphan*/  crop_left; int /*<<< orphan*/  crop_bottom; int /*<<< orphan*/  crop_top; int /*<<< orphan*/  sample_aspect_ratio; int /*<<< orphan*/  pict_type; int /*<<< orphan*/  key_frame; } ;
struct TYPE_10__ {scalar_t__ type; int /*<<< orphan*/  metadata; int /*<<< orphan*/ * buf; int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ AVFrameSideData ;
typedef  TYPE_2__ AVFrame ;
typedef  int /*<<< orphan*/  AVBufferRef ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AV_FRAME_DATA_PANSCAN ; 
 int /*<<< orphan*/  ENOMEM ; 
 void* av_buffer_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_dict_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* av_frame_new_side_data (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__* av_frame_new_side_data_from_buf (TYPE_2__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wipe_side_data (TYPE_2__*) ; 

__attribute__((used)) static int frame_copy_props(AVFrame *dst, const AVFrame *src, int force_copy)
{
    int i;

    dst->key_frame              = src->key_frame;
    dst->pict_type              = src->pict_type;
    dst->sample_aspect_ratio    = src->sample_aspect_ratio;
    dst->crop_top               = src->crop_top;
    dst->crop_bottom            = src->crop_bottom;
    dst->crop_left              = src->crop_left;
    dst->crop_right             = src->crop_right;
    dst->pts                    = src->pts;
    dst->repeat_pict            = src->repeat_pict;
    dst->interlaced_frame       = src->interlaced_frame;
    dst->top_field_first        = src->top_field_first;
    dst->palette_has_changed    = src->palette_has_changed;
    dst->sample_rate            = src->sample_rate;
    dst->opaque                 = src->opaque;
#if FF_API_PKT_PTS
FF_DISABLE_DEPRECATION_WARNINGS
    dst->pkt_pts                = src->pkt_pts;
FF_ENABLE_DEPRECATION_WARNINGS
#endif
    dst->pkt_dts                = src->pkt_dts;
    dst->pkt_pos                = src->pkt_pos;
    dst->pkt_size               = src->pkt_size;
    dst->pkt_duration           = src->pkt_duration;
    dst->reordered_opaque       = src->reordered_opaque;
    dst->quality                = src->quality;
    dst->best_effort_timestamp  = src->best_effort_timestamp;
    dst->coded_picture_number   = src->coded_picture_number;
    dst->display_picture_number = src->display_picture_number;
    dst->flags                  = src->flags;
    dst->decode_error_flags     = src->decode_error_flags;
    dst->color_primaries        = src->color_primaries;
    dst->color_trc              = src->color_trc;
    dst->colorspace             = src->colorspace;
    dst->color_range            = src->color_range;
    dst->chroma_location        = src->chroma_location;

    av_dict_copy(&dst->metadata, src->metadata, 0);

#if FF_API_ERROR_FRAME
FF_DISABLE_DEPRECATION_WARNINGS
    memcpy(dst->error, src->error, sizeof(dst->error));
FF_ENABLE_DEPRECATION_WARNINGS
#endif

    for (i = 0; i < src->nb_side_data; i++) {
        const AVFrameSideData *sd_src = src->side_data[i];
        AVFrameSideData *sd_dst;
        if (   sd_src->type == AV_FRAME_DATA_PANSCAN
            && (src->width != dst->width || src->height != dst->height))
            continue;
        if (force_copy) {
            sd_dst = av_frame_new_side_data(dst, sd_src->type,
                                            sd_src->size);
            if (!sd_dst) {
                wipe_side_data(dst);
                return AVERROR(ENOMEM);
            }
            memcpy(sd_dst->data, sd_src->data, sd_src->size);
        } else {
            AVBufferRef *ref = av_buffer_ref(sd_src->buf);
            sd_dst = av_frame_new_side_data_from_buf(dst, sd_src->type, ref);
            if (!sd_dst) {
                av_buffer_unref(&ref);
                wipe_side_data(dst);
                return AVERROR(ENOMEM);
            }
        }
        av_dict_copy(&sd_dst->metadata, sd_src->metadata, 0);
    }

#if FF_API_FRAME_QP
FF_DISABLE_DEPRECATION_WARNINGS
    dst->qscale_table = NULL;
    dst->qstride      = 0;
    dst->qscale_type  = 0;
    av_buffer_unref(&dst->qp_table_buf);
    if (src->qp_table_buf) {
        dst->qp_table_buf = av_buffer_ref(src->qp_table_buf);
        if (dst->qp_table_buf) {
            dst->qscale_table = dst->qp_table_buf->data;
            dst->qstride      = src->qstride;
            dst->qscale_type  = src->qscale_type;
        }
    }
FF_ENABLE_DEPRECATION_WARNINGS
#endif

    av_buffer_unref(&dst->opaque_ref);
    av_buffer_unref(&dst->private_ref);
    if (src->opaque_ref) {
        dst->opaque_ref = av_buffer_ref(src->opaque_ref);
        if (!dst->opaque_ref)
            return AVERROR(ENOMEM);
    }
    if (src->private_ref) {
        dst->private_ref = av_buffer_ref(src->private_ref);
        if (!dst->private_ref)
            return AVERROR(ENOMEM);
    }
    return 0;
}