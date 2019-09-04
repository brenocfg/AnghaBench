#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_16__ {unsigned int start; } ;
struct TYPE_15__ {int /*<<< orphan*/  container_ul; } ;
struct TYPE_14__ {int nb_streams; TYPE_2__** streams; int /*<<< orphan*/ * pb; TYPE_4__* priv_data; } ;
struct TYPE_13__ {unsigned int last_indexed_edit_unit; unsigned int edit_units_count; int content_package_rate; int essence_container_count; TYPE_9__ tc; } ;
struct TYPE_12__ {size_t index; } ;
struct TYPE_11__ {TYPE_3__* priv_data; TYPE_1__* codecpar; } ;
struct TYPE_10__ {scalar_t__ codec_type; } ;
typedef  TYPE_3__ MXFStreamContext ;
typedef  TYPE_4__ MXFContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_5__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ AVMEDIA_TYPE_AUDIO ; 
 scalar_t__ AVMEDIA_TYPE_DATA ; 
 int /*<<< orphan*/  av_timecode_get_smpte_from_framenum (TYPE_9__*,unsigned int) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wb64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  klv_encode_ber4_length (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  multiple_desc_ul ; 
 TYPE_8__* mxf_essence_container_uls ; 
 int /*<<< orphan*/  mxf_write_umid (TYPE_5__*,int) ; 
 int /*<<< orphan*/  system_metadata_pack_key ; 
 int /*<<< orphan*/  system_metadata_package_set_key ; 

__attribute__((used)) static void mxf_write_system_item(AVFormatContext *s)
{
    MXFContext *mxf = s->priv_data;
    AVIOContext *pb = s->pb;
    unsigned frame;
    uint32_t time_code;
    int i, system_item_bitmap = 0x58; // UL, user date/time stamp, picture present

    frame = mxf->last_indexed_edit_unit + mxf->edit_units_count;

    // write system metadata pack
    avio_write(pb, system_metadata_pack_key, 16);
    klv_encode_ber4_length(pb, 57);

    for (i = 0; i < s->nb_streams; i++) {
        if (s->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO)
            system_item_bitmap |= 0x4;
        else if (s->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_DATA)
            system_item_bitmap |= 0x2;
    }
    avio_w8(pb, system_item_bitmap);
    avio_w8(pb, mxf->content_package_rate); // content package rate
    avio_w8(pb, 0x00); // content package type
    avio_wb16(pb, 0x00); // channel handle
    avio_wb16(pb, (mxf->tc.start + frame) & 0xFFFF); // continuity count, supposed to overflow
    if (mxf->essence_container_count > 1)
        avio_write(pb, multiple_desc_ul, 16);
    else {
        MXFStreamContext *sc = s->streams[0]->priv_data;
        avio_write(pb, mxf_essence_container_uls[sc->index].container_ul, 16);
    }
    avio_w8(pb, 0);
    avio_wb64(pb, 0);
    avio_wb64(pb, 0); // creation date/time stamp

    avio_w8(pb, 0x81); // SMPTE 12M time code
    time_code = av_timecode_get_smpte_from_framenum(&mxf->tc, frame);
    avio_wb32(pb, time_code);
    avio_wb32(pb, 0); // binary group data
    avio_wb64(pb, 0);

    // write system metadata package set
    avio_write(pb, system_metadata_package_set_key, 16);
    klv_encode_ber4_length(pb, 35);
    avio_w8(pb, 0x83); // UMID
    avio_wb16(pb, 0x20);
    mxf_write_umid(s, 1);
}