#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int int64_t ;
typedef  int /*<<< orphan*/  FailingMuxerPacketData ;
typedef  int /*<<< orphan*/  AVPacket ;
typedef  int /*<<< orphan*/  AVFormatContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int AVERROR_BUG ; 
 int SLEEPTIME_50_MS ; 
 char* av_err2str (int) ; 
 int av_gettime_relative () ; 
 int /*<<< orphan*/  av_init_packet (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_packet_unref (int /*<<< orphan*/ *) ; 
 int av_write_frame (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int av_write_trailer (int /*<<< orphan*/ *) ; 
 int avformat_write_header (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int prepare_packet (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int fifo_overflow_drop_test(AVFormatContext *oc, AVDictionary **opts,
                                   const FailingMuxerPacketData *data)
{
    int ret = 0, i;
    int64_t write_pkt_start, write_pkt_end, duration;
    AVPacket pkt;

    av_init_packet(&pkt);

    ret = avformat_write_header(oc, opts);
    if (ret) {
        fprintf(stderr, "Unexpected write_header failure: %s\n",
                av_err2str(ret));
        return ret;
    }

    write_pkt_start = av_gettime_relative();
    for (i = 0; i < 6; i++ ) {
        ret = prepare_packet(&pkt, data, i);
        if (ret < 0) {
            fprintf(stderr, "Failed to prepare test packet: %s\n",
                    av_err2str(ret));
            goto fail;
        }
        ret = av_write_frame(oc, &pkt);
        av_packet_unref(&pkt);
        if (ret < 0) {
            break;
        }
    }
    write_pkt_end = av_gettime_relative();
    duration = write_pkt_end - write_pkt_start;
    if (duration > (SLEEPTIME_50_MS*6)/2) {
        fprintf(stderr, "Writing packets to fifo muxer took too much time while testing"
                        "buffer overflow with drop_pkts_on_overflow was on.\n");
        ret = AVERROR_BUG;
        goto fail;
    }

    if (ret) {
        fprintf(stderr, "Unexpected write_packet error: %s\n", av_err2str(ret));
        goto fail;
    }

    ret = av_write_trailer(oc);
    if (ret < 0)
        fprintf(stderr, "Unexpected write_trailer error: %s\n", av_err2str(ret));

    return ret;
fail:
    av_write_trailer(oc);
    return ret;
}