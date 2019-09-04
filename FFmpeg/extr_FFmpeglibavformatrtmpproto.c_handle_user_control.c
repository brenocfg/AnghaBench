#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_3__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_14__ {scalar_t__ swfsize; } ;
struct TYPE_13__ {int size; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ RTMPPacket ;
typedef  TYPE_3__ RTMPContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int AV_RB16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,...) ; 
 int gen_pong (TYPE_1__*,TYPE_3__*,TYPE_2__*) ; 
 int gen_swf_verification (TYPE_1__*,TYPE_3__*) ; 

__attribute__((used)) static int handle_user_control(URLContext *s, RTMPPacket *pkt)
{
    RTMPContext *rt = s->priv_data;
    int t, ret;

    if (pkt->size < 2) {
        av_log(s, AV_LOG_ERROR, "Too short user control packet (%d)\n",
               pkt->size);
        return AVERROR_INVALIDDATA;
    }

    t = AV_RB16(pkt->data);
    if (t == 6) { // PingRequest
        if ((ret = gen_pong(s, rt, pkt)) < 0)
            return ret;
    } else if (t == 26) {
        if (rt->swfsize) {
            if ((ret = gen_swf_verification(s, rt)) < 0)
                return ret;
        } else {
            av_log(s, AV_LOG_WARNING, "Ignoring SWFVerification request.\n");
        }
    }

    return 0;
}