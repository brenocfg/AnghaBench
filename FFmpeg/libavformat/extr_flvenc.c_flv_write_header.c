#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int codec_tag; } ;
struct TYPE_17__ {int nb_streams; TYPE_1__** streams; TYPE_2__* priv_data; TYPE_3__* pb; } ;
struct TYPE_16__ {scalar_t__ seekable; } ;
struct TYPE_15__ {int reserved; int flags; int /*<<< orphan*/  datastart_offset; int /*<<< orphan*/  video_par; int /*<<< orphan*/  audio_par; } ;
struct TYPE_14__ {TYPE_8__* codecpar; } ;
typedef  TYPE_2__ FLVContext ;
typedef  TYPE_3__ AVIOContext ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int FLV_HEADER_FLAG_HASAUDIO ; 
 int FLV_HEADER_FLAG_HASVIDEO ; 
 int FLV_NO_METADATA ; 
 int /*<<< orphan*/  avio_tell (TYPE_3__*) ; 
 int /*<<< orphan*/  avio_w8 (TYPE_3__*,int) ; 
 int /*<<< orphan*/  avio_wb24 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wb32 (TYPE_3__*,int) ; 
 int /*<<< orphan*/  avio_write (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  flv_write_codec_header (TYPE_4__*,TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_metadata (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int flv_write_header(AVFormatContext *s)
{
    int i;
    AVIOContext *pb = s->pb;
    FLVContext *flv = s->priv_data;

    avio_write(pb, "FLV", 3);
    avio_w8(pb, 1);
    avio_w8(pb, FLV_HEADER_FLAG_HASAUDIO * !!flv->audio_par +
                FLV_HEADER_FLAG_HASVIDEO * !!flv->video_par);
    avio_wb32(pb, 9);
    avio_wb32(pb, 0);

    for (i = 0; i < s->nb_streams; i++)
        if (s->streams[i]->codecpar->codec_tag == 5) {
            avio_w8(pb, 8);     // message type
            avio_wb24(pb, 0);   // include flags
            avio_wb24(pb, 0);   // time stamp
            avio_wb32(pb, 0);   // reserved
            avio_wb32(pb, 11);  // size
            flv->reserved = 5;
        }

    if (flv->flags & FLV_NO_METADATA) {
        pb->seekable = 0;
    } else {
        write_metadata(s, 0);
    }

    for (i = 0; i < s->nb_streams; i++) {
        flv_write_codec_header(s, s->streams[i]->codecpar, 0);
    }

    flv->datastart_offset = avio_tell(pb);
    return 0;
}