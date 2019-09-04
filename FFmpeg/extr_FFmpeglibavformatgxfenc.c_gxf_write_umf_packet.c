#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* int64_t ;
struct TYPE_9__ {int /*<<< orphan*/ * pb; TYPE_1__* priv_data; } ;
struct TYPE_8__ {void* umf_start_offset; void* umf_length; int /*<<< orphan*/  umf_media_size; int /*<<< orphan*/  umf_track_size; } ;
typedef  TYPE_1__ GXFContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  PKT_UMF ; 
 void* avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  gxf_write_packet_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gxf_write_umf_material_description (TYPE_2__*) ; 
 int /*<<< orphan*/  gxf_write_umf_media_description (TYPE_2__*) ; 
 int /*<<< orphan*/  gxf_write_umf_payload (TYPE_2__*) ; 
 int /*<<< orphan*/  gxf_write_umf_track_description (TYPE_2__*) ; 
 int updatePacketSize (int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static int gxf_write_umf_packet(AVFormatContext *s)
{
    GXFContext *gxf = s->priv_data;
    AVIOContext *pb = s->pb;
    int64_t pos = avio_tell(pb);

    gxf_write_packet_header(pb, PKT_UMF);

    /* preamble */
    avio_w8(pb, 3); /* first and last (only) packet */
    avio_wb32(pb, gxf->umf_length); /* data length */

    gxf->umf_start_offset = avio_tell(pb);
    gxf_write_umf_payload(s);
    gxf_write_umf_material_description(s);
    gxf->umf_track_size = gxf_write_umf_track_description(s);
    gxf->umf_media_size = gxf_write_umf_media_description(s);
    gxf->umf_length = avio_tell(pb) - gxf->umf_start_offset;
    return updatePacketSize(pb, pos);
}