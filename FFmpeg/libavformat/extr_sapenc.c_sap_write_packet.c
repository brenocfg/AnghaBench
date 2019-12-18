#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct SAPState {int last_time; int /*<<< orphan*/  ann_size; int /*<<< orphan*/  ann; int /*<<< orphan*/  ann_fd; } ;
typedef  int int64_t ;
struct TYPE_11__ {TYPE_1__** streams; struct SAPState* priv_data; } ;
struct TYPE_10__ {size_t stream_index; } ;
struct TYPE_9__ {TYPE_3__* priv_data; } ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECONNREFUSED ; 
 int av_gettime_relative () ; 
 int ff_write_chained (TYPE_3__*,int /*<<< orphan*/ ,TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int ffurl_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sap_write_packet(AVFormatContext *s, AVPacket *pkt)
{
    AVFormatContext *rtpctx;
    struct SAPState *sap = s->priv_data;
    int64_t now = av_gettime_relative();

    if (!sap->last_time || now - sap->last_time > 5000000) {
        int ret = ffurl_write(sap->ann_fd, sap->ann, sap->ann_size);
        /* Don't abort even if we get "Destination unreachable" */
        if (ret < 0 && ret != AVERROR(ECONNREFUSED))
            return ret;
        sap->last_time = now;
    }
    rtpctx = s->streams[pkt->stream_index]->priv_data;
    return ff_write_chained(rtpctx, 0, pkt, s, 0);
}