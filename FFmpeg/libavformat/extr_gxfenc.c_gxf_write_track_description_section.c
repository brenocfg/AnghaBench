#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_8__ {int nb_streams; TYPE_1__** streams; int /*<<< orphan*/ * pb; TYPE_2__* priv_data; } ;
struct TYPE_7__ {int /*<<< orphan*/  timecode_track; } ;
struct TYPE_6__ {int /*<<< orphan*/ * priv_data; } ;
typedef  TYPE_2__ GXFContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_wb16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gxf_write_track_description (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int updateSize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gxf_write_track_description_section(AVFormatContext *s)
{
    GXFContext *gxf = s->priv_data;
    AVIOContext *pb = s->pb;
    int64_t pos;
    int i;

    pos = avio_tell(pb);
    avio_wb16(pb, 0); /* size */
    for (i = 0; i < s->nb_streams; ++i)
        gxf_write_track_description(s, s->streams[i]->priv_data, i);

    gxf_write_track_description(s, &gxf->timecode_track, s->nb_streams);

    return updateSize(pb, pos);
}