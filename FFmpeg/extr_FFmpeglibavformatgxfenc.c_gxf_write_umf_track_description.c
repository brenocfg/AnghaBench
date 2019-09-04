#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_11__ {int nb_streams; TYPE_1__** streams; TYPE_4__* priv_data; int /*<<< orphan*/ * pb; } ;
struct TYPE_8__ {int media_info; } ;
struct TYPE_10__ {int umf_track_offset; int umf_start_offset; TYPE_2__ timecode_track; } ;
struct TYPE_9__ {int media_info; } ;
struct TYPE_7__ {TYPE_3__* priv_data; } ;
typedef  TYPE_3__ GXFStreamContext ;
typedef  TYPE_4__ GXFContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_5__ AVFormatContext ;

/* Variables and functions */
 int avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_wl16 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int gxf_write_umf_track_description(AVFormatContext *s)
{
    AVIOContext *pb = s->pb;
    GXFContext *gxf = s->priv_data;
    int64_t pos = avio_tell(pb);
    int i;

    gxf->umf_track_offset = pos - gxf->umf_start_offset;
    for (i = 0; i < s->nb_streams; ++i) {
        GXFStreamContext *sc = s->streams[i]->priv_data;
        avio_wl16(pb, sc->media_info);
        avio_wl16(pb, 1);
    }

    avio_wl16(pb, gxf->timecode_track.media_info);
    avio_wl16(pb, 1);

    return avio_tell(pb) - pos;
}