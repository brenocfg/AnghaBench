#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  WriterContext ;
struct TYPE_15__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_14__ {double MaxCLL; double MaxFALL; } ;
struct TYPE_13__ {int /*<<< orphan*/  max_luminance; int /*<<< orphan*/  min_luminance; scalar_t__ has_luminance; int /*<<< orphan*/ * white_point; int /*<<< orphan*/ ** display_primaries; scalar_t__ has_primaries; } ;
struct TYPE_12__ {scalar_t__ type; int size; scalar_t__ data; } ;
struct TYPE_11__ {scalar_t__ projection; double padding; scalar_t__ roll; scalar_t__ pitch; scalar_t__ yaw; } ;
struct TYPE_10__ {int flags; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  SectionID ;
typedef  TYPE_1__ AVStereo3D ;
typedef  TYPE_2__ AVSphericalMapping ;
typedef  TYPE_3__ AVPacketSideData ;
typedef  TYPE_4__ AVMasteringDisplayMetadata ;
typedef  TYPE_5__ AVContentLightMetadata ;
typedef  TYPE_6__ AVCodecParameters ;

/* Variables and functions */
 scalar_t__ AV_PKT_DATA_CONTENT_LIGHT_LEVEL ; 
 scalar_t__ AV_PKT_DATA_DISPLAYMATRIX ; 
 scalar_t__ AV_PKT_DATA_MASTERING_DISPLAY_METADATA ; 
 scalar_t__ AV_PKT_DATA_SKIP_SAMPLES ; 
 scalar_t__ AV_PKT_DATA_SPHERICAL ; 
 scalar_t__ AV_PKT_DATA_STEREO3D ; 
 double AV_RL32 (scalar_t__) ; 
 double AV_RL8 (scalar_t__) ; 
 scalar_t__ AV_SPHERICAL_CUBEMAP ; 
 scalar_t__ AV_SPHERICAL_EQUIRECTANGULAR_TILE ; 
 int AV_STEREO3D_FLAG_INVERT ; 
 double av_display_rotation_get (int /*<<< orphan*/ *) ; 
 char* av_packet_side_data_name (scalar_t__) ; 
 char const* av_spherical_projection_name (scalar_t__) ; 
 int /*<<< orphan*/  av_spherical_tile_bounds (TYPE_2__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,size_t*,size_t*,size_t*) ; 
 char const* av_stereo3d_type_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_int (char*,double) ; 
 int /*<<< orphan*/  print_q (char*,int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  print_str (char*,char const*) ; 
 int /*<<< orphan*/  writer_print_integers (int /*<<< orphan*/ *,char*,scalar_t__,int,char*,int,int,int) ; 
 int /*<<< orphan*/  writer_print_section_footer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writer_print_section_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_pkt_side_data(WriterContext *w,
                                AVCodecParameters *par,
                                const AVPacketSideData *side_data,
                                int nb_side_data,
                                SectionID id_data_list,
                                SectionID id_data)
{
    int i;

    writer_print_section_header(w, id_data_list);
    for (i = 0; i < nb_side_data; i++) {
        const AVPacketSideData *sd = &side_data[i];
        const char *name = av_packet_side_data_name(sd->type);

        writer_print_section_header(w, id_data);
        print_str("side_data_type", name ? name : "unknown");
        if (sd->type == AV_PKT_DATA_DISPLAYMATRIX && sd->size >= 9*4) {
            writer_print_integers(w, "displaymatrix", sd->data, 9, " %11d", 3, 4, 1);
            print_int("rotation", av_display_rotation_get((int32_t *)sd->data));
        } else if (sd->type == AV_PKT_DATA_STEREO3D) {
            const AVStereo3D *stereo = (AVStereo3D *)sd->data;
            print_str("type", av_stereo3d_type_name(stereo->type));
            print_int("inverted", !!(stereo->flags & AV_STEREO3D_FLAG_INVERT));
        } else if (sd->type == AV_PKT_DATA_SPHERICAL) {
            const AVSphericalMapping *spherical = (AVSphericalMapping *)sd->data;
            print_str("projection", av_spherical_projection_name(spherical->projection));
            if (spherical->projection == AV_SPHERICAL_CUBEMAP) {
                print_int("padding", spherical->padding);
            } else if (spherical->projection == AV_SPHERICAL_EQUIRECTANGULAR_TILE) {
                size_t l, t, r, b;
                av_spherical_tile_bounds(spherical, par->width, par->height,
                                         &l, &t, &r, &b);
                print_int("bound_left", l);
                print_int("bound_top", t);
                print_int("bound_right", r);
                print_int("bound_bottom", b);
            }

            print_int("yaw", (double) spherical->yaw / (1 << 16));
            print_int("pitch", (double) spherical->pitch / (1 << 16));
            print_int("roll", (double) spherical->roll / (1 << 16));
        } else if (sd->type == AV_PKT_DATA_SKIP_SAMPLES && sd->size == 10) {
            print_int("skip_samples",    AV_RL32(sd->data));
            print_int("discard_padding", AV_RL32(sd->data + 4));
            print_int("skip_reason",     AV_RL8(sd->data + 8));
            print_int("discard_reason",  AV_RL8(sd->data + 9));
        } else if (sd->type == AV_PKT_DATA_MASTERING_DISPLAY_METADATA) {
            AVMasteringDisplayMetadata *metadata = (AVMasteringDisplayMetadata *)sd->data;

            if (metadata->has_primaries) {
                print_q("red_x", metadata->display_primaries[0][0], '/');
                print_q("red_y", metadata->display_primaries[0][1], '/');
                print_q("green_x", metadata->display_primaries[1][0], '/');
                print_q("green_y", metadata->display_primaries[1][1], '/');
                print_q("blue_x", metadata->display_primaries[2][0], '/');
                print_q("blue_y", metadata->display_primaries[2][1], '/');

                print_q("white_point_x", metadata->white_point[0], '/');
                print_q("white_point_y", metadata->white_point[1], '/');
            }

            if (metadata->has_luminance) {
                print_q("min_luminance", metadata->min_luminance, '/');
                print_q("max_luminance", metadata->max_luminance, '/');
            }
        } else if (sd->type == AV_PKT_DATA_CONTENT_LIGHT_LEVEL) {
            AVContentLightMetadata *metadata = (AVContentLightMetadata *)sd->data;
            print_int("max_content", metadata->MaxCLL);
            print_int("max_average", metadata->MaxFALL);
        }
        writer_print_section_footer(w);
    }
    writer_print_section_footer(w);
}