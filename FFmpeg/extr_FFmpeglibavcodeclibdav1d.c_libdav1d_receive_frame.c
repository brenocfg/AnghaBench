#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_47__   TYPE_9__ ;
typedef  struct TYPE_46__   TYPE_8__ ;
typedef  struct TYPE_45__   TYPE_7__ ;
typedef  struct TYPE_44__   TYPE_6__ ;
typedef  struct TYPE_43__   TYPE_5__ ;
typedef  struct TYPE_42__   TYPE_4__ ;
typedef  struct TYPE_41__   TYPE_3__ ;
typedef  struct TYPE_40__   TYPE_2__ ;
typedef  struct TYPE_39__   TYPE_1__ ;
typedef  struct TYPE_38__   TYPE_16__ ;
typedef  struct TYPE_37__   TYPE_15__ ;
typedef  struct TYPE_36__   TYPE_14__ ;
typedef  struct TYPE_35__   TYPE_13__ ;
typedef  struct TYPE_34__   TYPE_12__ ;
typedef  struct TYPE_33__   TYPE_11__ ;
typedef  struct TYPE_32__   TYPE_10__ ;

/* Type definitions */
typedef  enum AVColorTransferCharacteristic { ____Placeholder_AVColorTransferCharacteristic } AVColorTransferCharacteristic ;
typedef  enum AVColorSpace { ____Placeholder_AVColorSpace } AVColorSpace ;
typedef  enum AVColorPrimaries { ____Placeholder_AVColorPrimaries } AVColorPrimaries ;
struct TYPE_45__ {int /*<<< orphan*/  duration; int /*<<< orphan*/  offset; int /*<<< orphan*/  timestamp; } ;
struct TYPE_33__ {TYPE_7__ m; int /*<<< orphan*/  sz; } ;
struct TYPE_47__ {int /*<<< orphan*/  c; TYPE_11__ data; } ;
struct TYPE_46__ {scalar_t__ draining; } ;
struct TYPE_44__ {int /*<<< orphan*/  max_frame_average_light_level; int /*<<< orphan*/  max_content_light_level; } ;
struct TYPE_43__ {int /*<<< orphan*/  min_luminance; int /*<<< orphan*/  max_luminance; int /*<<< orphan*/ * white_point; int /*<<< orphan*/ ** primaries; } ;
struct TYPE_42__ {int frame_type; } ;
struct TYPE_41__ {int /*<<< orphan*/  duration; int /*<<< orphan*/  size; int /*<<< orphan*/  offset; int /*<<< orphan*/  timestamp; } ;
struct TYPE_40__ {size_t hbd; int chr; scalar_t__ color_range; scalar_t__ trc; scalar_t__ pri; scalar_t__ mtrx; int /*<<< orphan*/  profile; } ;
struct TYPE_39__ {size_t layout; scalar_t__ w; scalar_t__ h; } ;
struct TYPE_38__ {scalar_t__ width; scalar_t__ height; int colorspace; int color_primaries; int color_trc; int /*<<< orphan*/  color_range; int /*<<< orphan*/  chroma_sample_location; int /*<<< orphan*/  pix_fmt; int /*<<< orphan*/  profile; TYPE_8__* internal; TYPE_9__* priv_data; } ;
struct TYPE_37__ {int /*<<< orphan*/  MaxFALL; int /*<<< orphan*/  MaxCLL; } ;
struct TYPE_36__ {scalar_t__ width; scalar_t__ height; int colorspace; int color_primaries; int color_trc; int key_frame; int /*<<< orphan*/  pict_type; int /*<<< orphan*/  pkt_duration; int /*<<< orphan*/  pkt_size; int /*<<< orphan*/  pkt_pos; int /*<<< orphan*/  pkt_dts; int /*<<< orphan*/  best_effort_timestamp; int /*<<< orphan*/  pts; int /*<<< orphan*/  color_range; int /*<<< orphan*/  chroma_location; int /*<<< orphan*/  format; int /*<<< orphan*/ * linesize; int /*<<< orphan*/ ** data; int /*<<< orphan*/ * buf; } ;
struct TYPE_35__ {int has_primaries; int has_luminance; void* min_luminance; void* max_luminance; void** white_point; void*** display_primaries; } ;
struct TYPE_34__ {int /*<<< orphan*/ * buf; int /*<<< orphan*/  duration; int /*<<< orphan*/  pos; int /*<<< orphan*/  pts; scalar_t__ size; int /*<<< orphan*/  data; int /*<<< orphan*/  member_0; } ;
struct TYPE_32__ {TYPE_6__* content_light; TYPE_5__* mastering_display; TYPE_4__* frame_hdr; TYPE_3__ m; TYPE_2__* seq_hdr; TYPE_1__ p; int /*<<< orphan*/ * stride; int /*<<< orphan*/ ** data; int /*<<< orphan*/  allocator_data; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_9__ Libdav1dContext ;
typedef  TYPE_10__ Dav1dPicture ;
typedef  TYPE_11__ Dav1dData ;
typedef  TYPE_12__ AVPacket ;
typedef  TYPE_13__ AVMasteringDisplayMetadata ;
typedef  TYPE_14__ AVFrame ;
typedef  TYPE_15__ AVContentLightMetadata ;
typedef  TYPE_16__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVCHROMA_LOC_LEFT ; 
 int /*<<< orphan*/  AVCHROMA_LOC_TOPLEFT ; 
 int /*<<< orphan*/  AVCOL_RANGE_JPEG ; 
 int /*<<< orphan*/  AVCOL_RANGE_MPEG ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_I ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_P ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_SP ; 
#define  DAV1D_CHR_COLOCATED 133 
#define  DAV1D_CHR_VERTICAL 132 
#define  DAV1D_FRAME_TYPE_INTER 131 
#define  DAV1D_FRAME_TYPE_INTRA 130 
#define  DAV1D_FRAME_TYPE_KEY 129 
#define  DAV1D_FRAME_TYPE_SWITCH 128 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_assert0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_buffer_ref (int /*<<< orphan*/ ) ; 
 TYPE_15__* av_content_light_metadata_create_side_data (TYPE_14__*) ; 
 int /*<<< orphan*/  av_frame_unref (TYPE_14__*) ; 
 void* av_make_q (int /*<<< orphan*/ ,int) ; 
 TYPE_13__* av_mastering_display_metadata_create_side_data (TYPE_14__*) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_12__*) ; 
 int dav1d_data_wrap (TYPE_11__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int dav1d_get_picture (int /*<<< orphan*/ ,TYPE_10__*) ; 
 int /*<<< orphan*/  dav1d_picture_unref (TYPE_10__*) ; 
 int dav1d_send_data (int /*<<< orphan*/ ,TYPE_11__*) ; 
 int ff_decode_get_packet (TYPE_16__*,TYPE_12__*) ; 
 int ff_set_dimensions (TYPE_16__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  libdav1d_data_free ; 
 int /*<<< orphan*/ ** pix_fmt ; 

__attribute__((used)) static int libdav1d_receive_frame(AVCodecContext *c, AVFrame *frame)
{
    Libdav1dContext *dav1d = c->priv_data;
    Dav1dData *data = &dav1d->data;
    Dav1dPicture pic = { 0 }, *p = &pic;
    int res;

    if (!data->sz) {
        AVPacket pkt = { 0 };

        res = ff_decode_get_packet(c, &pkt);
        if (res < 0 && res != AVERROR_EOF)
            return res;

        if (pkt.size) {
            res = dav1d_data_wrap(data, pkt.data, pkt.size, libdav1d_data_free, pkt.buf);
            if (res < 0) {
                av_packet_unref(&pkt);
                return res;
            }

            data->m.timestamp = pkt.pts;
            data->m.offset = pkt.pos;
            data->m.duration = pkt.duration;

            pkt.buf = NULL;
            av_packet_unref(&pkt);
        }
    }

    res = dav1d_send_data(dav1d->c, data);
    if (res < 0) {
        if (res == AVERROR(EINVAL))
            res = AVERROR_INVALIDDATA;
        if (res != AVERROR(EAGAIN))
            return res;
    }

    res = dav1d_get_picture(dav1d->c, p);
    if (res < 0) {
        if (res == AVERROR(EINVAL))
            res = AVERROR_INVALIDDATA;
        else if (res == AVERROR(EAGAIN) && c->internal->draining)
            res = AVERROR_EOF;

        return res;
    }

    av_assert0(p->data[0] != NULL);

    // This requires the custom allocator above
    frame->buf[0] = av_buffer_ref(p->allocator_data);
    if (!frame->buf[0]) {
        dav1d_picture_unref(p);
        return AVERROR(ENOMEM);
    }

    frame->data[0] = p->data[0];
    frame->data[1] = p->data[1];
    frame->data[2] = p->data[2];
    frame->linesize[0] = p->stride[0];
    frame->linesize[1] = p->stride[1];
    frame->linesize[2] = p->stride[1];

    c->profile = p->seq_hdr->profile;
    frame->format = c->pix_fmt = pix_fmt[p->p.layout][p->seq_hdr->hbd];
    frame->width = p->p.w;
    frame->height = p->p.h;
    if (c->width != p->p.w || c->height != p->p.h) {
        res = ff_set_dimensions(c, p->p.w, p->p.h);
        if (res < 0)
            goto fail;
    }

    switch (p->seq_hdr->chr) {
    case DAV1D_CHR_VERTICAL:
        frame->chroma_location = c->chroma_sample_location = AVCHROMA_LOC_LEFT;
        break;
    case DAV1D_CHR_COLOCATED:
        frame->chroma_location = c->chroma_sample_location = AVCHROMA_LOC_TOPLEFT;
        break;
    }
    frame->colorspace = c->colorspace = (enum AVColorSpace) p->seq_hdr->mtrx;
    frame->color_primaries = c->color_primaries = (enum AVColorPrimaries) p->seq_hdr->pri;
    frame->color_trc = c->color_trc = (enum AVColorTransferCharacteristic) p->seq_hdr->trc;
    frame->color_range = c->color_range = p->seq_hdr->color_range ? AVCOL_RANGE_JPEG : AVCOL_RANGE_MPEG;

    // match timestamps and packet size
    frame->pts = frame->best_effort_timestamp = p->m.timestamp;
#if FF_API_PKT_PTS
FF_DISABLE_DEPRECATION_WARNINGS
    frame->pkt_pts = p->m.timestamp;
FF_ENABLE_DEPRECATION_WARNINGS
#endif
    frame->pkt_dts = p->m.timestamp;
    frame->pkt_pos = p->m.offset;
    frame->pkt_size = p->m.size;
    frame->pkt_duration = p->m.duration;
    frame->key_frame = p->frame_hdr->frame_type == DAV1D_FRAME_TYPE_KEY;

    switch (p->frame_hdr->frame_type) {
    case DAV1D_FRAME_TYPE_KEY:
    case DAV1D_FRAME_TYPE_INTRA:
        frame->pict_type = AV_PICTURE_TYPE_I;
        break;
    case DAV1D_FRAME_TYPE_INTER:
        frame->pict_type = AV_PICTURE_TYPE_P;
        break;
    case DAV1D_FRAME_TYPE_SWITCH:
        frame->pict_type = AV_PICTURE_TYPE_SP;
        break;
    default:
        res = AVERROR_INVALIDDATA;
        goto fail;
    }

    if (p->mastering_display) {
        AVMasteringDisplayMetadata *mastering = av_mastering_display_metadata_create_side_data(frame);
        if (!mastering) {
            res = AVERROR(ENOMEM);
            goto fail;
        }

        for (int i = 0; i < 3; i++) {
            mastering->display_primaries[i][0] = av_make_q(p->mastering_display->primaries[i][0], 1 << 16);
            mastering->display_primaries[i][1] = av_make_q(p->mastering_display->primaries[i][1], 1 << 16);
        }
        mastering->white_point[0] = av_make_q(p->mastering_display->white_point[0], 1 << 16);
        mastering->white_point[1] = av_make_q(p->mastering_display->white_point[1], 1 << 16);

        mastering->max_luminance = av_make_q(p->mastering_display->max_luminance, 1 << 8);
        mastering->min_luminance = av_make_q(p->mastering_display->min_luminance, 1 << 14);

        mastering->has_primaries = 1;
        mastering->has_luminance = 1;
    }
    if (p->content_light) {
        AVContentLightMetadata *light = av_content_light_metadata_create_side_data(frame);
        if (!light) {
            res = AVERROR(ENOMEM);
            goto fail;
        }
        light->MaxCLL = p->content_light->max_content_light_level;
        light->MaxFALL = p->content_light->max_frame_average_light_level;
    }

    res = 0;
fail:
    dav1d_picture_unref(p);
    if (res < 0)
        av_frame_unref(frame);
    return res;
}