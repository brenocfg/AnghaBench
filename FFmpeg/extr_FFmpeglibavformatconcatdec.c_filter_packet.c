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
struct TYPE_3__ {scalar_t__ bsf; } ;
typedef  TYPE_1__ ConcatStream ;
typedef  int /*<<< orphan*/  AVPacket ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EAGAIN ; 
 int av_bsf_receive_packet (scalar_t__,int /*<<< orphan*/ *) ; 
 int av_bsf_send_packet (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  av_packet_unref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int filter_packet(AVFormatContext *avf, ConcatStream *cs, AVPacket *pkt)
{
    int ret;

    if (cs->bsf) {
        ret = av_bsf_send_packet(cs->bsf, pkt);
        if (ret < 0) {
            av_log(avf, AV_LOG_ERROR, "h264_mp4toannexb filter "
                   "failed to send input packet\n");
            av_packet_unref(pkt);
            return ret;
        }

        while (!ret)
            ret = av_bsf_receive_packet(cs->bsf, pkt);

        if (ret < 0 && (ret != AVERROR(EAGAIN) && ret != AVERROR_EOF)) {
            av_log(avf, AV_LOG_ERROR, "h264_mp4toannexb filter "
                   "failed to receive output packet\n");
            return ret;
        }
    }
    return 0;
}