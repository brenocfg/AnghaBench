#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_17__ {int nb_streams; TYPE_5__** streams; int /*<<< orphan*/ * pb; TYPE_4__* priv_data; } ;
struct TYPE_16__ {TYPE_2__* codecpar; TYPE_3__* priv_data; } ;
struct TYPE_12__ {int /*<<< orphan*/  drop; } ;
struct TYPE_14__ {int media_info; int /*<<< orphan*/  sample_size; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  track_type; } ;
struct TYPE_15__ {int umf_media_offset; int umf_start_offset; TYPE_1__ tc; TYPE_3__ timecode_track; int /*<<< orphan*/  nb_fields; } ;
struct TYPE_13__ {int codec_id; } ;
typedef  TYPE_3__ GXFStreamContext ;
typedef  TYPE_4__ GXFContext ;
typedef  TYPE_5__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_6__ AVFormatContext ;

/* Variables and functions */
#define  AV_CODEC_ID_DVVIDEO 131 
#define  AV_CODEC_ID_MPEG1VIDEO 130 
#define  AV_CODEC_ID_MPEG2VIDEO 129 
#define  AV_CODEC_ID_PCM_S16LE 128 
 int /*<<< orphan*/  ES_NAME_PATTERN ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wb16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wl16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wl32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gxf_write_umf_media_audio (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  gxf_write_umf_media_dv (int /*<<< orphan*/ *,TYPE_3__*,TYPE_5__*) ; 
 int /*<<< orphan*/  gxf_write_umf_media_mpeg (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  gxf_write_umf_media_timecode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gxf_write_umf_media_description(AVFormatContext *s)
{
    GXFContext *gxf = s->priv_data;
    AVIOContext *pb = s->pb;
    int64_t pos;
    int i, j;

    pos = avio_tell(pb);
    gxf->umf_media_offset = pos - gxf->umf_start_offset;
    for (i = 0; i <= s->nb_streams; ++i) {
        GXFStreamContext *sc;
        int64_t startpos, curpos;

        if (i == s->nb_streams)
            sc = &gxf->timecode_track;
        else
            sc = s->streams[i]->priv_data;

        startpos = avio_tell(pb);
        avio_wl16(pb, 0); /* length */
        avio_wl16(pb, sc->media_info);
        avio_wl16(pb, 0); /* reserved */
        avio_wl16(pb, 0); /* reserved */
        avio_wl32(pb, gxf->nb_fields);
        avio_wl32(pb, 0); /* attributes rw, ro */
        avio_wl32(pb, 0); /* mark in */
        avio_wl32(pb, gxf->nb_fields); /* mark out */
        avio_write(pb, ES_NAME_PATTERN, strlen(ES_NAME_PATTERN));
        avio_wb16(pb, sc->media_info);
        for (j = strlen(ES_NAME_PATTERN)+2; j < 88; j++)
            avio_w8(pb, 0);
        avio_wl32(pb, sc->track_type);
        avio_wl32(pb, sc->sample_rate);
        avio_wl32(pb, sc->sample_size);
        avio_wl32(pb, 0); /* reserved */

        if (sc == &gxf->timecode_track)
            gxf_write_umf_media_timecode(pb, gxf->tc.drop);
        else {
            AVStream *st = s->streams[i];
            switch (st->codecpar->codec_id) {
            case AV_CODEC_ID_MPEG1VIDEO:
            case AV_CODEC_ID_MPEG2VIDEO:
                gxf_write_umf_media_mpeg(pb, st);
                break;
            case AV_CODEC_ID_PCM_S16LE:
                gxf_write_umf_media_audio(pb, sc);
                break;
            case AV_CODEC_ID_DVVIDEO:
                gxf_write_umf_media_dv(pb, sc, st);
                break;
            }
        }

        curpos = avio_tell(pb);
        avio_seek(pb, startpos, SEEK_SET);
        avio_wl16(pb, curpos - startpos);
        avio_seek(pb, curpos, SEEK_SET);
    }
    return avio_tell(pb) - pos;
}