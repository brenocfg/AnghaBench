#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  host ;
struct TYPE_7__ {int /*<<< orphan*/  url; TYPE_1__* priv_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  real_challenge; } ;
typedef  TYPE_1__ RTSPState ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  RTSP_LOWER_TRANSPORT_TCP ; 
 int /*<<< orphan*/  av_url_split (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ff_rtsp_make_setup_request (TYPE_2__*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_rtsp_undo_setup (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int resetup_tcp(AVFormatContext *s)
{
    RTSPState *rt = s->priv_data;
    char host[1024];
    int port;

    av_url_split(NULL, 0, NULL, 0, host, sizeof(host), &port, NULL, 0,
                 s->url);
    ff_rtsp_undo_setup(s, 0);
    return ff_rtsp_make_setup_request(s, host, port, RTSP_LOWER_TRANSPORT_TCP,
                                      rt->real_challenge);
}