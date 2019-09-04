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
typedef  int uint8_t ;
struct AVFormatContext {int nb_streams; int /*<<< orphan*/  pb; TYPE_3__** streams; } ;
struct TYPE_5__ {int den; unsigned int num; } ;
struct TYPE_6__ {TYPE_2__ avg_frame_rate; TYPE_1__* codecpar; } ;
struct TYPE_4__ {scalar_t__ codec_type; } ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_log (struct AVFormatContext*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avio_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int roq_write_header(struct AVFormatContext *s)
{
    uint8_t header[] = {
        0x84, 0x10, 0xFF, 0xFF, 0xFF, 0xFF, /* fps: */ 0x1E, 0x00
    };
    int n;

// set the actual fps
    for(n=0;n<s->nb_streams;n++) {
        if (s->streams[n]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            unsigned int fps;

            if (s->streams[n]->avg_frame_rate.den != 1) {
                av_log(s, AV_LOG_ERROR, "Frame rate must be integer\n");
                return AVERROR(EINVAL);
            }

            if ((fps=s->streams[n]->avg_frame_rate.num) > 255) {
                av_log(s, AV_LOG_ERROR, "Frame rate may not exceed 255fps\n");
                return AVERROR(EINVAL);
            }

            if (fps != 30) {
                av_log(s, AV_LOG_WARNING, "For vintage compatibility fps must be 30\n");
            }

            header[6] = fps;
            break;
        }
    }

    avio_write(s->pb, header, 8);
    avio_flush(s->pb);

    return 0;
}