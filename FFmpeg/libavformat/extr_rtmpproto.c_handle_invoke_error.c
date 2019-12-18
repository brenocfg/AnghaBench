#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  tmpstr ;
struct TYPE_10__ {TYPE_3__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_12__ {int do_reconnect; scalar_t__ live; } ;
struct TYPE_11__ {int size; int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ RTMPPacket ;
typedef  TYPE_3__ RTMPContext ;

/* Variables and functions */
 int AVERROR_UNKNOWN ; 
 int AV_LOG_DEBUG ; 
 int AV_LOG_ERROR ; 
 int AV_LOG_VERBOSE ; 
 int AV_LOG_WARNING ; 
 int /*<<< orphan*/  av_free (char*) ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_amf_get_field_value (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,char*,int /*<<< orphan*/ *,int) ; 
 int find_tracked_method (TYPE_1__*,TYPE_2__*,int,char**) ; 
 int handle_connect_error (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static int handle_invoke_error(URLContext *s, RTMPPacket *pkt)
{
    RTMPContext *rt = s->priv_data;
    const uint8_t *data_end = pkt->data + pkt->size;
    char *tracked_method = NULL;
    int level = AV_LOG_ERROR;
    uint8_t tmpstr[256];
    int ret;

    if ((ret = find_tracked_method(s, pkt, 9, &tracked_method)) < 0)
        return ret;

    if (!ff_amf_get_field_value(pkt->data + 9, data_end,
                                "description", tmpstr, sizeof(tmpstr))) {
        if (tracked_method && (!strcmp(tracked_method, "_checkbw")      ||
                               !strcmp(tracked_method, "releaseStream") ||
                               !strcmp(tracked_method, "FCSubscribe")   ||
                               !strcmp(tracked_method, "FCPublish"))) {
            /* Gracefully ignore Adobe-specific historical artifact errors. */
            level = AV_LOG_WARNING;
            ret = 0;
        } else if (tracked_method && !strcmp(tracked_method, "getStreamLength")) {
            level = rt->live ? AV_LOG_DEBUG : AV_LOG_WARNING;
            ret = 0;
        } else if (tracked_method && !strcmp(tracked_method, "connect")) {
            ret = handle_connect_error(s, tmpstr);
            if (!ret) {
                rt->do_reconnect = 1;
                level = AV_LOG_VERBOSE;
            }
        } else
            ret = AVERROR_UNKNOWN;
        av_log(s, level, "Server error: %s\n", tmpstr);
    }

    av_free(tracked_method);
    return ret;
}