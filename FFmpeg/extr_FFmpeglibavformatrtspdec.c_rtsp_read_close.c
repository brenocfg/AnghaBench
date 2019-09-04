#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* priv_data; } ;
struct TYPE_7__ {int rtsp_flags; int /*<<< orphan*/  real_setup_cache; int /*<<< orphan*/ * real_setup; int /*<<< orphan*/  control_uri; } ;
typedef  TYPE_1__ RTSPState ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int RTSP_FLAG_LISTEN ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_network_close () ; 
 int /*<<< orphan*/  ff_rtsp_close_connections (TYPE_2__*) ; 
 int /*<<< orphan*/  ff_rtsp_close_streams (TYPE_2__*) ; 
 int /*<<< orphan*/  ff_rtsp_send_cmd_async (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rtsp_read_close(AVFormatContext *s)
{
    RTSPState *rt = s->priv_data;

    if (!(rt->rtsp_flags & RTSP_FLAG_LISTEN))
        ff_rtsp_send_cmd_async(s, "TEARDOWN", rt->control_uri, NULL);

    ff_rtsp_close_streams(s);
    ff_rtsp_close_connections(s);
    ff_network_close();
    rt->real_setup = NULL;
    av_freep(&rt->real_setup_cache);
    return 0;
}