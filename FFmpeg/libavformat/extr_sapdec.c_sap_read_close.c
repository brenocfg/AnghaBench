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
struct SAPState {int /*<<< orphan*/  sdp; scalar_t__ ann_fd; scalar_t__ sdp_ctx; } ;
struct TYPE_3__ {struct SAPState* priv_data; } ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avformat_close_input (scalar_t__*) ; 
 int /*<<< orphan*/  ff_network_close () ; 
 int /*<<< orphan*/  ffurl_close (scalar_t__) ; 

__attribute__((used)) static int sap_read_close(AVFormatContext *s)
{
    struct SAPState *sap = s->priv_data;
    if (sap->sdp_ctx)
        avformat_close_input(&sap->sdp_ctx);
    if (sap->ann_fd)
        ffurl_close(sap->ann_fd);
    av_freep(&sap->sdp);
    ff_network_close();
    return 0;
}