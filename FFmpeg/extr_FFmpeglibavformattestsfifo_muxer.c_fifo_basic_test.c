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
typedef  int /*<<< orphan*/  FailingMuxerPacketData ;
typedef  int /*<<< orphan*/  AVPacket ;
typedef  int /*<<< orphan*/  AVFormatContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 char* av_err2str (int) ; 
 int /*<<< orphan*/  av_init_packet (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_packet_unref (int /*<<< orphan*/ *) ; 
 int av_write_frame (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int av_write_trailer (int /*<<< orphan*/ *) ; 
 int avformat_write_header (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int prepare_packet (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int fifo_basic_test(AVFormatContext *oc, AVDictionary **opts,
                             const FailingMuxerPacketData *pkt_data)
{
    int ret = 0, i;
    AVPacket pkt;

    av_init_packet(&pkt);


    ret = avformat_write_header(oc, opts);
    if (ret) {
        fprintf(stderr, "Unexpected write_header failure: %s\n",
                av_err2str(ret));
        goto fail;
    }

    for (i = 0; i < 15; i++ ) {
        ret = prepare_packet(&pkt, pkt_data, i);
        if (ret < 0) {
            fprintf(stderr, "Failed to prepare test packet: %s\n",
                    av_err2str(ret));
            goto write_trailer_and_fail;
        }
        ret = av_write_frame(oc, &pkt);
        av_packet_unref(&pkt);
        if (ret < 0) {
            fprintf(stderr, "Unexpected write_frame error: %s\n",
                    av_err2str(ret));
            goto write_trailer_and_fail;
        }
    }

    ret = av_write_frame(oc, NULL);
    if (ret < 0) {
        fprintf(stderr, "Unexpected write_frame error during flushing: %s\n",
                av_err2str(ret));
        goto write_trailer_and_fail;
    }

    ret = av_write_trailer(oc);
    if (ret < 0) {
        fprintf(stderr, "Unexpected write_trailer error during flushing: %s\n",
                av_err2str(ret));
        goto fail;
    }

    return ret;
write_trailer_and_fail:
    av_write_trailer(oc);
fail:
    return ret;
}