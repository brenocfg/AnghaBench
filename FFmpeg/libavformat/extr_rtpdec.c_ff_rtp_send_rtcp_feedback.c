#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  URLContext ;
struct TYPE_6__ {scalar_t__ last_feedback_time; scalar_t__ ssrc; int /*<<< orphan*/  dynamic_protocol_context; TYPE_1__* handler; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* need_keyframe ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ RTPDemuxContext ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 scalar_t__ MIN_FEEDBACK_INTERVAL ; 
 int RTCP_PSFB ; 
 int RTCP_RTPFB ; 
 int RTP_VERSION ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 
 scalar_t__ av_gettime_relative () ; 
 int avio_close_dyn_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  avio_flush (int /*<<< orphan*/ *) ; 
 scalar_t__ avio_open_dyn_buf (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ffurl_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int find_missing_packets (TYPE_2__*,int*,int*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

int ff_rtp_send_rtcp_feedback(RTPDemuxContext *s, URLContext *fd,
                              AVIOContext *avio)
{
    int len, need_keyframe, missing_packets;
    AVIOContext *pb;
    uint8_t *buf;
    int64_t now;
    uint16_t first_missing = 0, missing_mask = 0;

    if (!fd && !avio)
        return -1;

    need_keyframe = s->handler && s->handler->need_keyframe &&
                    s->handler->need_keyframe(s->dynamic_protocol_context);
    missing_packets = find_missing_packets(s, &first_missing, &missing_mask);

    if (!need_keyframe && !missing_packets)
        return 0;

    /* Send new feedback if enough time has elapsed since the last
     * feedback packet. */

    now = av_gettime_relative();
    if (s->last_feedback_time &&
        (now - s->last_feedback_time) < MIN_FEEDBACK_INTERVAL)
        return 0;
    s->last_feedback_time = now;

    if (!fd)
        pb = avio;
    else if (avio_open_dyn_buf(&pb) < 0)
        return -1;

    if (need_keyframe) {
        avio_w8(pb, (RTP_VERSION << 6) | 1); /* PLI */
        avio_w8(pb, RTCP_PSFB);
        avio_wb16(pb, 2); /* length in words - 1 */
        // our own SSRC: we use the server's SSRC + 1 to avoid conflicts
        avio_wb32(pb, s->ssrc + 1);
        avio_wb32(pb, s->ssrc); // server SSRC
    }

    if (missing_packets) {
        avio_w8(pb, (RTP_VERSION << 6) | 1); /* NACK */
        avio_w8(pb, RTCP_RTPFB);
        avio_wb16(pb, 3); /* length in words - 1 */
        avio_wb32(pb, s->ssrc + 1);
        avio_wb32(pb, s->ssrc); // server SSRC

        avio_wb16(pb, first_missing);
        avio_wb16(pb, missing_mask);
    }

    avio_flush(pb);
    if (!fd)
        return 0;
    len = avio_close_dyn_buf(pb, &buf);
    if (len > 0 && buf) {
        ffurl_write(fd, buf, len);
        av_free(buf);
    }
    return 0;
}