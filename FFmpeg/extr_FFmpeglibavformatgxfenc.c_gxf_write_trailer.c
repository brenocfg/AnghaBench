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
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_9__ {int /*<<< orphan*/ * pb; TYPE_1__* priv_data; } ;
struct TYPE_8__ {int map_offsets_nb; int /*<<< orphan*/ * map_offsets; int /*<<< orphan*/ * flt_entries; } ;
typedef  TYPE_1__ GXFContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  avio_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_audio_interleave_close (TYPE_2__*) ; 
 int /*<<< orphan*/  gxf_write_eos_packet (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gxf_write_flt_packet (TYPE_2__*) ; 
 int gxf_write_map_packet (TYPE_2__*,int) ; 
 int /*<<< orphan*/  gxf_write_umf_packet (TYPE_2__*) ; 

__attribute__((used)) static int gxf_write_trailer(AVFormatContext *s)
{
    GXFContext *gxf = s->priv_data;
    AVIOContext *pb = s->pb;
    int64_t end;
    int i;
    int ret;

    ff_audio_interleave_close(s);

    gxf_write_eos_packet(pb);
    end = avio_tell(pb);
    avio_seek(pb, 0, SEEK_SET);
    /* overwrite map, flt and umf packets with new values */
    if ((ret = gxf_write_map_packet(s, 1)) < 0)
        return ret;
    gxf_write_flt_packet(s);
    gxf_write_umf_packet(s);
    avio_flush(pb);
    /* update duration in all map packets */
    for (i = 1; i < gxf->map_offsets_nb; i++) {
        avio_seek(pb, gxf->map_offsets[i], SEEK_SET);
        if ((ret = gxf_write_map_packet(s, 1)) < 0)
            return ret;
        avio_flush(pb);
    }

    avio_seek(pb, end, SEEK_SET);

    av_freep(&gxf->flt_entries);
    av_freep(&gxf->map_offsets);

    return 0;
}