#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_10__ {int /*<<< orphan*/  pb; TYPE_1__* priv_data; } ;
struct TYPE_9__ {scalar_t__ pts; scalar_t__ duration; char* data; int size; } ;
struct TYPE_8__ {int /*<<< orphan*/  index; } ;
typedef  TYPE_1__ SRTContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  AV_PKT_DATA_SUBTITLE_POSITION ; 
 int AV_RL32 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * av_packet_get_side_data (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  avio_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int srt_write_packet(AVFormatContext *avf, AVPacket *pkt)
{
    SRTContext *srt = avf->priv_data;

    int64_t s = pkt->pts, e, d = pkt->duration;
    int size, x1 = -1, y1 = -1, x2 = -1, y2 = -1;
    const uint8_t *p;

    p = av_packet_get_side_data(pkt, AV_PKT_DATA_SUBTITLE_POSITION, &size);
    if (p && size == 16) {
        x1 = AV_RL32(p     );
        y1 = AV_RL32(p +  4);
        x2 = AV_RL32(p +  8);
        y2 = AV_RL32(p + 12);
    }

#if FF_API_CONVERGENCE_DURATION
FF_DISABLE_DEPRECATION_WARNINGS
    if (d <= 0)
        /* For backward compatibility, fallback to convergence_duration. */
        d = pkt->convergence_duration;
FF_ENABLE_DEPRECATION_WARNINGS
#endif
    if (s == AV_NOPTS_VALUE || d < 0) {
        av_log(avf, AV_LOG_WARNING,
               "Insufficient timestamps in event number %d.\n", srt->index);
        return 0;
    }
    e = s + d;
    avio_printf(avf->pb, "%d\n%02d:%02d:%02d,%03d --> %02d:%02d:%02d,%03d",
                   srt->index,
                   (int)(s / 3600000),      (int)(s / 60000) % 60,
                   (int)(s /    1000) % 60, (int)(s %  1000),
                   (int)(e / 3600000),      (int)(e / 60000) % 60,
                   (int)(e /    1000) % 60, (int)(e %  1000));
    if (p)
        avio_printf(avf->pb, "  X1:%03d X2:%03d Y1:%03d Y2:%03d",
                    x1, x2, y1, y2);
    avio_printf(avf->pb, "\n");

    avio_write(avf->pb, pkt->data, pkt->size);
    avio_write(avf->pb, "\n\n", 2);
    srt->index++;
    return 0;
}