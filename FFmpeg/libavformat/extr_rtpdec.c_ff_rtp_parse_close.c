#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  srtp; } ;
typedef  TYPE_1__ RTPDemuxContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_free (TYPE_1__*) ; 
 int /*<<< orphan*/  ff_rtp_reset_packet_queue (TYPE_1__*) ; 
 int /*<<< orphan*/  ff_srtp_free (int /*<<< orphan*/ *) ; 

void ff_rtp_parse_close(RTPDemuxContext *s)
{
    ff_rtp_reset_packet_queue(s);
    ff_srtp_free(&s->srtp);
    av_free(s);
}