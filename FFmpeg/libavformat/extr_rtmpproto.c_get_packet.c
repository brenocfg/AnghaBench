#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {TYPE_3__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_21__ {scalar_t__ state; scalar_t__ bytes_read; scalar_t__ last_bytes_read; scalar_t__ receive_report_size; int /*<<< orphan*/  is_input; scalar_t__ do_reconnect; scalar_t__ last_timestamp; int /*<<< orphan*/ * nb_prev_pkt; int /*<<< orphan*/ * prev_pkt; int /*<<< orphan*/  in_chunk_size; int /*<<< orphan*/  stream; } ;
struct TYPE_20__ {scalar_t__ type; int /*<<< orphan*/  size; scalar_t__ timestamp; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ RTMPPacket ;
typedef  TYPE_3__ RTMPContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EIO ; 
 scalar_t__ RTMP_PT_AUDIO ; 
 scalar_t__ RTMP_PT_METADATA ; 
 scalar_t__ RTMP_PT_NOTIFY ; 
 scalar_t__ RTMP_PT_VIDEO ; 
 scalar_t__ STATE_PLAYING ; 
 scalar_t__ STATE_PUBLISHING ; 
 scalar_t__ STATE_RECEIVING ; 
 scalar_t__ STATE_SEEKING ; 
 scalar_t__ STATE_SENDING ; 
 scalar_t__ STATE_STOPPED ; 
 int append_flv_data (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ff_rtmp_packet_destroy (TYPE_2__*) ; 
 int ff_rtmp_packet_read (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int gen_bytes_read (TYPE_1__*,TYPE_3__*,scalar_t__) ; 
 int handle_metadata (TYPE_3__*,TYPE_2__*) ; 
 int handle_notify (TYPE_1__*,TYPE_2__*) ; 
 int rtmp_parse_result (TYPE_1__*,TYPE_3__*,TYPE_2__*) ; 

__attribute__((used)) static int get_packet(URLContext *s, int for_header)
{
    RTMPContext *rt = s->priv_data;
    int ret;

    if (rt->state == STATE_STOPPED)
        return AVERROR_EOF;

    for (;;) {
        RTMPPacket rpkt = { 0 };
        if ((ret = ff_rtmp_packet_read(rt->stream, &rpkt,
                                       rt->in_chunk_size, &rt->prev_pkt[0],
                                       &rt->nb_prev_pkt[0])) <= 0) {
            if (ret == 0) {
                return AVERROR(EAGAIN);
            } else {
                return AVERROR(EIO);
            }
        }

        // Track timestamp for later use
        rt->last_timestamp = rpkt.timestamp;

        rt->bytes_read += ret;
        if (rt->bytes_read - rt->last_bytes_read > rt->receive_report_size) {
            av_log(s, AV_LOG_DEBUG, "Sending bytes read report\n");
            if ((ret = gen_bytes_read(s, rt, rpkt.timestamp + 1)) < 0) {
                ff_rtmp_packet_destroy(&rpkt);
                return ret;
            }
            rt->last_bytes_read = rt->bytes_read;
        }

        ret = rtmp_parse_result(s, rt, &rpkt);

        // At this point we must check if we are in the seek state and continue
        // with the next packet. handle_invoke will get us out of this state
        // when the right message is encountered
        if (rt->state == STATE_SEEKING) {
            ff_rtmp_packet_destroy(&rpkt);
            // We continue, let the natural flow of things happen:
            // AVERROR(EAGAIN) or handle_invoke gets us out of here
            continue;
        }

        if (ret < 0) {//serious error in current packet
            ff_rtmp_packet_destroy(&rpkt);
            return ret;
        }
        if (rt->do_reconnect && for_header) {
            ff_rtmp_packet_destroy(&rpkt);
            return 0;
        }
        if (rt->state == STATE_STOPPED) {
            ff_rtmp_packet_destroy(&rpkt);
            return AVERROR_EOF;
        }
        if (for_header && (rt->state == STATE_PLAYING    ||
                           rt->state == STATE_PUBLISHING ||
                           rt->state == STATE_SENDING    ||
                           rt->state == STATE_RECEIVING)) {
            ff_rtmp_packet_destroy(&rpkt);
            return 0;
        }
        if (!rpkt.size || !rt->is_input) {
            ff_rtmp_packet_destroy(&rpkt);
            continue;
        }
        if (rpkt.type == RTMP_PT_VIDEO || rpkt.type == RTMP_PT_AUDIO) {
            ret = append_flv_data(rt, &rpkt, 0);
            ff_rtmp_packet_destroy(&rpkt);
            return ret;
        } else if (rpkt.type == RTMP_PT_NOTIFY) {
            ret = handle_notify(s, &rpkt);
            ff_rtmp_packet_destroy(&rpkt);
            return ret;
        } else if (rpkt.type == RTMP_PT_METADATA) {
            ret = handle_metadata(rt, &rpkt);
            ff_rtmp_packet_destroy(&rpkt);
            return ret;
        }
        ff_rtmp_packet_destroy(&rpkt);
    }
}