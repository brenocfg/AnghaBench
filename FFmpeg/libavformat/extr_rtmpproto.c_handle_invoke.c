#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/ * priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_15__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ RTMPPacket ;
typedef  int /*<<< orphan*/  RTMPContext ;

/* Variables and functions */
 scalar_t__ ff_amf_match_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int gen_check_bw (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int handle_invoke_error (TYPE_1__*,TYPE_2__*) ; 
 int handle_invoke_result (TYPE_1__*,TYPE_2__*) ; 
 int handle_invoke_status (TYPE_1__*,TYPE_2__*) ; 
 int send_invoke_response (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static int handle_invoke(URLContext *s, RTMPPacket *pkt)
{
    RTMPContext *rt = s->priv_data;
    int ret = 0;

    //TODO: check for the messages sent for wrong state?
    if (ff_amf_match_string(pkt->data, pkt->size, "_error")) {
        if ((ret = handle_invoke_error(s, pkt)) < 0)
            return ret;
    } else if (ff_amf_match_string(pkt->data, pkt->size, "_result")) {
        if ((ret = handle_invoke_result(s, pkt)) < 0)
            return ret;
    } else if (ff_amf_match_string(pkt->data, pkt->size, "onStatus")) {
        if ((ret = handle_invoke_status(s, pkt)) < 0)
            return ret;
    } else if (ff_amf_match_string(pkt->data, pkt->size, "onBWDone")) {
        if ((ret = gen_check_bw(s, rt)) < 0)
            return ret;
    } else if (ff_amf_match_string(pkt->data, pkt->size, "releaseStream") ||
               ff_amf_match_string(pkt->data, pkt->size, "FCPublish")     ||
               ff_amf_match_string(pkt->data, pkt->size, "publish")       ||
               ff_amf_match_string(pkt->data, pkt->size, "play")          ||
               ff_amf_match_string(pkt->data, pkt->size, "_checkbw")      ||
               ff_amf_match_string(pkt->data, pkt->size, "createStream")) {
        if ((ret = send_invoke_response(s, pkt)) < 0)
            return ret;
    }

    return ret;
}