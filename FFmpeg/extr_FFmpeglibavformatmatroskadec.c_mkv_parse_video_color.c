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

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_25__ {scalar_t__ MaxFALL; scalar_t__ MaxCLL; } ;
struct TYPE_24__ {int has_primaries; int has_luminance; void* min_luminance; void* max_luminance; void** white_point; void*** display_primaries; } ;
struct TYPE_23__ {TYPE_3__* codecpar; } ;
struct TYPE_22__ {int const r_x; int const r_y; int const g_x; int const g_y; int const b_x; int const b_y; int const white_x; int const white_y; int const max_luminance; int const min_luminance; } ;
struct TYPE_17__ {int /*<<< orphan*/  nb_elem; TYPE_4__* elem; } ;
struct TYPE_18__ {TYPE_1__ color; } ;
struct TYPE_21__ {TYPE_2__ video; } ;
struct TYPE_20__ {scalar_t__ matrix_coefficients; scalar_t__ primaries; scalar_t__ transfer_characteristics; scalar_t__ range; int chroma_siting_horz; int chroma_siting_vert; scalar_t__ max_fall; scalar_t__ max_cll; TYPE_6__ mastering_meta; } ;
struct TYPE_19__ {scalar_t__ color_space; scalar_t__ color_primaries; scalar_t__ color_trc; scalar_t__ color_range; int /*<<< orphan*/  chroma_location; } ;
typedef  TYPE_4__ MatroskaTrackVideoColor ;
typedef  TYPE_5__ MatroskaTrack ;
typedef  TYPE_6__ MatroskaMasteringMeta ;
typedef  TYPE_7__ AVStream ;
typedef  TYPE_8__ AVMasteringDisplayMetadata ;
typedef  TYPE_9__ AVContentLightMetadata ;

/* Variables and functions */
 scalar_t__ AVCOL_PRI_RESERVED ; 
 scalar_t__ AVCOL_PRI_RESERVED0 ; 
 scalar_t__ AVCOL_RANGE_JPEG ; 
 scalar_t__ AVCOL_RANGE_UNSPECIFIED ; 
 scalar_t__ AVCOL_SPC_RESERVED ; 
 scalar_t__ AVCOL_TRC_RESERVED ; 
 scalar_t__ AVCOL_TRC_RESERVED0 ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_PKT_DATA_CONTENT_LIGHT_LEVEL ; 
 int /*<<< orphan*/  AV_PKT_DATA_MASTERING_DISPLAY_METADATA ; 
 int /*<<< orphan*/  ENOMEM ; 
 int MATROSKA_COLOUR_CHROMASITINGHORZ_NB ; 
 int MATROSKA_COLOUR_CHROMASITINGHORZ_UNDETERMINED ; 
 int MATROSKA_COLOUR_CHROMASITINGVERT_NB ; 
 int MATROSKA_COLOUR_CHROMASITINGVERT_UNDETERMINED ; 
 TYPE_9__* av_content_light_metadata_alloc (size_t*) ; 
 int /*<<< orphan*/  av_freep (TYPE_9__**) ; 
 void* av_make_q (int /*<<< orphan*/ ,int const) ; 
 int av_stream_add_side_data (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ av_stream_new_side_data (TYPE_7__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  avcodec_chroma_pos_to_enum (int,int) ; 
 int /*<<< orphan*/  memset (TYPE_8__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  round (int const) ; 

__attribute__((used)) static int mkv_parse_video_color(AVStream *st, const MatroskaTrack *track) {
    const MatroskaTrackVideoColor *color = track->video.color.elem;
    const MatroskaMasteringMeta *mastering_meta;
    int has_mastering_primaries, has_mastering_luminance;

    if (!track->video.color.nb_elem)
        return 0;

    mastering_meta = &color->mastering_meta;
    // Mastering primaries are CIE 1931 coords, and must be > 0.
    has_mastering_primaries =
        mastering_meta->r_x > 0 && mastering_meta->r_y > 0 &&
        mastering_meta->g_x > 0 && mastering_meta->g_y > 0 &&
        mastering_meta->b_x > 0 && mastering_meta->b_y > 0 &&
        mastering_meta->white_x > 0 && mastering_meta->white_y > 0;
    has_mastering_luminance = mastering_meta->max_luminance > 0;

    if (color->matrix_coefficients != AVCOL_SPC_RESERVED)
        st->codecpar->color_space = color->matrix_coefficients;
    if (color->primaries != AVCOL_PRI_RESERVED &&
        color->primaries != AVCOL_PRI_RESERVED0)
        st->codecpar->color_primaries = color->primaries;
    if (color->transfer_characteristics != AVCOL_TRC_RESERVED &&
        color->transfer_characteristics != AVCOL_TRC_RESERVED0)
        st->codecpar->color_trc = color->transfer_characteristics;
    if (color->range != AVCOL_RANGE_UNSPECIFIED &&
        color->range <= AVCOL_RANGE_JPEG)
        st->codecpar->color_range = color->range;
    if (color->chroma_siting_horz != MATROSKA_COLOUR_CHROMASITINGHORZ_UNDETERMINED &&
        color->chroma_siting_vert != MATROSKA_COLOUR_CHROMASITINGVERT_UNDETERMINED &&
        color->chroma_siting_horz  < MATROSKA_COLOUR_CHROMASITINGHORZ_NB &&
        color->chroma_siting_vert  < MATROSKA_COLOUR_CHROMASITINGVERT_NB) {
        st->codecpar->chroma_location =
            avcodec_chroma_pos_to_enum((color->chroma_siting_horz - 1) << 7,
                                       (color->chroma_siting_vert - 1) << 7);
    }
    if (color->max_cll && color->max_fall) {
        size_t size = 0;
        int ret;
        AVContentLightMetadata *metadata = av_content_light_metadata_alloc(&size);
        if (!metadata)
            return AVERROR(ENOMEM);
        ret = av_stream_add_side_data(st, AV_PKT_DATA_CONTENT_LIGHT_LEVEL,
                                      (uint8_t *)metadata, size);
        if (ret < 0) {
            av_freep(&metadata);
            return ret;
        }
        metadata->MaxCLL  = color->max_cll;
        metadata->MaxFALL = color->max_fall;
    }

    if (has_mastering_primaries || has_mastering_luminance) {
        // Use similar rationals as other standards.
        const int chroma_den = 50000;
        const int luma_den = 10000;
        AVMasteringDisplayMetadata *metadata =
            (AVMasteringDisplayMetadata*) av_stream_new_side_data(
                st, AV_PKT_DATA_MASTERING_DISPLAY_METADATA,
                sizeof(AVMasteringDisplayMetadata));
        if (!metadata) {
            return AVERROR(ENOMEM);
        }
        memset(metadata, 0, sizeof(AVMasteringDisplayMetadata));
        if (has_mastering_primaries) {
            metadata->display_primaries[0][0] = av_make_q(
                round(mastering_meta->r_x * chroma_den), chroma_den);
            metadata->display_primaries[0][1] = av_make_q(
                round(mastering_meta->r_y * chroma_den), chroma_den);
            metadata->display_primaries[1][0] = av_make_q(
                round(mastering_meta->g_x * chroma_den), chroma_den);
            metadata->display_primaries[1][1] = av_make_q(
                round(mastering_meta->g_y * chroma_den), chroma_den);
            metadata->display_primaries[2][0] = av_make_q(
                round(mastering_meta->b_x * chroma_den), chroma_den);
            metadata->display_primaries[2][1] = av_make_q(
                round(mastering_meta->b_y * chroma_den), chroma_den);
            metadata->white_point[0] = av_make_q(
                round(mastering_meta->white_x * chroma_den), chroma_den);
            metadata->white_point[1] = av_make_q(
                round(mastering_meta->white_y * chroma_den), chroma_den);
            metadata->has_primaries = 1;
        }
        if (has_mastering_luminance) {
            metadata->max_luminance = av_make_q(
                round(mastering_meta->max_luminance * luma_den), luma_den);
            metadata->min_luminance = av_make_q(
                round(mastering_meta->min_luminance * luma_den), luma_den);
            metadata->has_luminance = 1;
        }
    }
    return 0;
}