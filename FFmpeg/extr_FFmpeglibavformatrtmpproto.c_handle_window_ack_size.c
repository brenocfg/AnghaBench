#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_3__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_9__ {int receive_report_size; } ;
struct TYPE_8__ {int size; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ RTMPPacket ;
typedef  TYPE_3__ RTMPContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int AV_RB32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int handle_window_ack_size(URLContext *s, RTMPPacket *pkt)
{
    RTMPContext *rt = s->priv_data;

    if (pkt->size < 4) {
        av_log(s, AV_LOG_ERROR,
               "Too short window acknowledgement size packet (%d)\n",
               pkt->size);
        return AVERROR_INVALIDDATA;
    }

    rt->receive_report_size = AV_RB32(pkt->data);
    if (rt->receive_report_size <= 0) {
        av_log(s, AV_LOG_ERROR, "Incorrect window acknowledgement size %d\n",
               rt->receive_report_size);
        return AVERROR_INVALIDDATA;
    }
    av_log(s, AV_LOG_DEBUG, "Window acknowledgement size = %d\n", rt->receive_report_size);
    // Send an Acknowledgement packet after receiving half the maximum
    // size, to make sure the peer can keep on sending without waiting
    // for acknowledgements.
    rt->receive_report_size >>= 1;

    return 0;
}