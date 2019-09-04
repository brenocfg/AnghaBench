#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_10__ {int /*<<< orphan*/ * pb; TYPE_3__* priv_data; } ;
struct TYPE_8__ {int hh; int mm; int ss; int ff; int /*<<< orphan*/  drop; int /*<<< orphan*/  color; } ;
struct TYPE_7__ {int den; } ;
struct TYPE_9__ {int nb_fields; int flags; int audio_tracks; int mpeg_tracks; TYPE_2__ tc; TYPE_1__ time_base; } ;
typedef  TYPE_3__ GXFContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int GXF_TIMECODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  avio_wl16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wl32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wl64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_parse_creation_time_metadata (TYPE_4__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int gxf_write_umf_material_description(AVFormatContext *s)
{
    GXFContext *gxf = s->priv_data;
    AVIOContext *pb = s->pb;
    int timecode_base = gxf->time_base.den == 60000 ? 60 : 50;
    int64_t timestamp = 0;
    uint64_t nb_fields;
    uint32_t timecode_in; // timecode at mark in
    uint32_t timecode_out; // timecode at mark out

    ff_parse_creation_time_metadata(s, &timestamp, 1);

    timecode_in = GXF_TIMECODE(gxf->tc.color, gxf->tc.drop,
                               gxf->tc.hh, gxf->tc.mm,
                               gxf->tc.ss, gxf->tc.ff);

    nb_fields = gxf->nb_fields +
                gxf->tc.hh * (timecode_base * 3600) +
                gxf->tc.mm * (timecode_base * 60)   +
                gxf->tc.ss * timecode_base          +
                gxf->tc.ff;

    timecode_out = GXF_TIMECODE(gxf->tc.color, gxf->tc.drop,
                                nb_fields / (timecode_base * 3600) % 24,
                                nb_fields / (timecode_base * 60)   % 60,
                                nb_fields /  timecode_base % 60,
                                nb_fields %  timecode_base);

    avio_wl32(pb, gxf->flags);
    avio_wl32(pb, gxf->nb_fields); /* length of the longest track */
    avio_wl32(pb, gxf->nb_fields); /* length of the shortest track */
    avio_wl32(pb, 0); /* mark in */
    avio_wl32(pb, gxf->nb_fields); /* mark out */
    avio_wl32(pb, timecode_in); /* timecode mark in */
    avio_wl32(pb, timecode_out); /* timecode mark out */
    avio_wl64(pb, timestamp); /* modification time */
    avio_wl64(pb, timestamp); /* creation time */
    avio_wl16(pb, 0); /* reserved */
    avio_wl16(pb, 0); /* reserved */
    avio_wl16(pb, gxf->audio_tracks);
    avio_wl16(pb, 1); /* timecode track count */
    avio_wl16(pb, 0); /* reserved */
    avio_wl16(pb, gxf->mpeg_tracks);
    return 48;
}