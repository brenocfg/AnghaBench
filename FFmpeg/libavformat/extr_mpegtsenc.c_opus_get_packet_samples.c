#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int size; int* data; } ;
typedef  TYPE_1__ AVPacket ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int opus_get_packet_samples(AVFormatContext *s, AVPacket *pkt)
{
    static const int durations[32] = {
      480, 960, 1920, 2880,       /* Silk NB */
      480, 960, 1920, 2880,       /* Silk MB */
      480, 960, 1920, 2880,       /* Silk WB */
      480, 960,                   /* Hybrid SWB */
      480, 960,                   /* Hybrid FB */
      120, 240, 480, 960,         /* CELT NB */
      120, 240, 480, 960,         /* CELT NB */
      120, 240, 480, 960,         /* CELT NB */
      120, 240, 480, 960,         /* CELT NB */
    };
    int toc, frame_duration, nframes, duration;

    if (pkt->size < 1)
        return 0;

    toc = pkt->data[0];

    frame_duration = durations[toc >> 3];
    switch (toc & 3) {
    case 0:
        nframes = 1;
        break;
    case 1:
        nframes = 2;
        break;
    case 2:
        nframes = 2;
        break;
    case 3:
        if (pkt->size < 2)
            return 0;
        nframes = pkt->data[1] & 63;
        break;
    }

    duration = nframes * frame_duration;
    if (duration > 5760) {
        av_log(s, AV_LOG_WARNING,
               "Opus packet duration > 120 ms, invalid");
        return 0;
    }

    return duration;
}