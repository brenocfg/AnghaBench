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
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_3__ {scalar_t__ base_timestamp; scalar_t__ last_rtcp_timestamp; int /*<<< orphan*/  rtcp_ts_offset; int /*<<< orphan*/  last_rtcp_ntp_time; int /*<<< orphan*/  first_rtcp_ntp_time; int /*<<< orphan*/  last_rtcp_reception_time; int /*<<< orphan*/  ic; } ;
typedef  TYPE_1__ RTPDemuxContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_NOPTS_VALUE ; 
 int AV_RB16 (unsigned char const*) ; 
 scalar_t__ AV_RB32 (unsigned char const*) ; 
 int /*<<< orphan*/  AV_RB64 (unsigned char const*) ; 
 int FFMIN (int,int) ; 
#define  RTCP_BYE 129 
#define  RTCP_SR 128 
 int /*<<< orphan*/  av_gettime_relative () ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int rtcp_parse_packet(RTPDemuxContext *s, const unsigned char *buf,
                             int len)
{
    int payload_len;
    while (len >= 4) {
        payload_len = FFMIN(len, (AV_RB16(buf + 2) + 1) * 4);

        switch (buf[1]) {
        case RTCP_SR:
            if (payload_len < 20) {
                av_log(s->ic, AV_LOG_ERROR, "Invalid RTCP SR packet length\n");
                return AVERROR_INVALIDDATA;
            }

            s->last_rtcp_reception_time = av_gettime_relative();
            s->last_rtcp_ntp_time  = AV_RB64(buf + 8);
            s->last_rtcp_timestamp = AV_RB32(buf + 16);
            if (s->first_rtcp_ntp_time == AV_NOPTS_VALUE) {
                s->first_rtcp_ntp_time = s->last_rtcp_ntp_time;
                if (!s->base_timestamp)
                    s->base_timestamp = s->last_rtcp_timestamp;
                s->rtcp_ts_offset = (int32_t)(s->last_rtcp_timestamp - s->base_timestamp);
            }

            break;
        case RTCP_BYE:
            return -RTCP_BYE;
        }

        buf += payload_len;
        len -= payload_len;
    }
    return -1;
}