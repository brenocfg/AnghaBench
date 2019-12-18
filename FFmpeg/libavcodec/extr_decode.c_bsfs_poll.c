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
struct TYPE_8__ {TYPE_1__* internal; } ;
struct TYPE_7__ {int nb_bsfs; int /*<<< orphan*/ * bsfs; } ;
struct TYPE_6__ {TYPE_2__ filter; } ;
typedef  TYPE_2__ DecodeFilterContext ;
typedef  int /*<<< orphan*/  AVPacket ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EAGAIN ; 
 int av_bsf_receive_packet (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int av_bsf_send_packet (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  av_packet_unref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bsfs_poll(AVCodecContext *avctx, AVPacket *pkt)
{
    DecodeFilterContext *s = &avctx->internal->filter;
    int idx, ret;

    /* start with the last filter in the chain */
    idx = s->nb_bsfs - 1;
    while (idx >= 0) {
        /* request a packet from the currently selected filter */
        ret = av_bsf_receive_packet(s->bsfs[idx], pkt);
        if (ret == AVERROR(EAGAIN)) {
            /* no packets available, try the next filter up the chain */
            idx--;
            continue;
        } else if (ret < 0 && ret != AVERROR_EOF) {
            return ret;
        }

        /* got a packet or EOF -- pass it to the caller or to the next filter
         * down the chain */
        if (idx == s->nb_bsfs - 1) {
            return ret;
        } else {
            idx++;
            ret = av_bsf_send_packet(s->bsfs[idx], ret < 0 ? NULL : pkt);
            if (ret < 0) {
                av_log(avctx, AV_LOG_ERROR,
                       "Error pre-processing a packet before decoding\n");
                av_packet_unref(pkt);
                return ret;
            }
        }
    }

    return AVERROR(EAGAIN);
}