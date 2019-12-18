#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct AVFormatContext {int nb_streams; TYPE_3__** streams; int /*<<< orphan*/  pb; } ;
struct TYPE_4__ {int /*<<< orphan*/  den; int /*<<< orphan*/  num; } ;
struct TYPE_6__ {TYPE_1__ avg_frame_rate; TYPE_2__* codecpar; } ;
struct TYPE_5__ {scalar_t__ codec_id; char* extradata; int extradata_size; } ;
typedef  TYPE_1__ AVRational ;
typedef  TYPE_2__ AVCodecParameters ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_MICRODVD ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (struct AVFormatContext*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avio_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int microdvd_write_header(struct AVFormatContext *s)
{
    AVCodecParameters *par = s->streams[0]->codecpar;
    AVRational framerate = s->streams[0]->avg_frame_rate;

    if (s->nb_streams != 1 || par->codec_id != AV_CODEC_ID_MICRODVD) {
        av_log(s, AV_LOG_ERROR, "Exactly one MicroDVD stream is needed.\n");
        return -1;
    }

    if (par->extradata && par->extradata_size > 0) {
        avio_write(s->pb, "{DEFAULT}{}", 11);
        avio_write(s->pb, par->extradata, par->extradata_size);
        avio_flush(s->pb);
    }

    avpriv_set_pts_info(s->streams[0], 64, framerate.num, framerate.den);
    return 0;
}