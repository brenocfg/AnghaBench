#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_8__ {int /*<<< orphan*/ * pb; TYPE_1__* priv_data; } ;
struct TYPE_7__ {int map_offsets_nb; int /*<<< orphan*/ * map_offsets; } ;
typedef  TYPE_1__ GXFContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  PKT_MAP ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int av_reallocp_array (int /*<<< orphan*/ **,int,int) ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gxf_write_material_data_section (TYPE_2__*) ; 
 int /*<<< orphan*/  gxf_write_packet_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gxf_write_track_description_section (TYPE_2__*) ; 
 int updatePacketSize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gxf_write_map_packet(AVFormatContext *s, int rewrite)
{
    GXFContext *gxf = s->priv_data;
    AVIOContext *pb = s->pb;
    int64_t pos = avio_tell(pb);

    if (!rewrite) {
        if (!(gxf->map_offsets_nb % 30)) {
            int err;
            if ((err = av_reallocp_array(&gxf->map_offsets,
                                         gxf->map_offsets_nb + 30,
                                         sizeof(*gxf->map_offsets))) < 0) {
                gxf->map_offsets_nb = 0;
                av_log(s, AV_LOG_ERROR, "could not realloc map offsets\n");
                return err;
            }
        }
        gxf->map_offsets[gxf->map_offsets_nb++] = pos; // do not increment here
    }

    gxf_write_packet_header(pb, PKT_MAP);

    /* preamble */
    avio_w8(pb, 0xE0); /* version */
    avio_w8(pb, 0xFF); /* reserved */

    gxf_write_material_data_section(s);
    gxf_write_track_description_section(s);

    return updatePacketSize(pb, pos);
}