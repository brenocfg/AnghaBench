#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int prev_ret; int /*<<< orphan*/  srtp; scalar_t__ srtp_enabled; } ;
typedef  TYPE_1__ RTPDemuxContext ;
typedef  int /*<<< orphan*/  AVPacket ;

/* Variables and functions */
 scalar_t__ ff_srtp_decrypt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int has_next_packet (TYPE_1__*) ; 
 int rtp_parse_one_packet (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int) ; 
 int rtp_parse_queued_packet (TYPE_1__*,int /*<<< orphan*/ *) ; 

int ff_rtp_parse_packet(RTPDemuxContext *s, AVPacket *pkt,
                        uint8_t **bufptr, int len)
{
    int rv;
    if (s->srtp_enabled && bufptr && ff_srtp_decrypt(&s->srtp, *bufptr, &len) < 0)
        return -1;
    rv = rtp_parse_one_packet(s, pkt, bufptr, len);
    s->prev_ret = rv;
    while (rv < 0 && has_next_packet(s))
        rv = rtp_parse_queued_packet(s, pkt);
    return rv ? rv : has_next_packet(s);
}