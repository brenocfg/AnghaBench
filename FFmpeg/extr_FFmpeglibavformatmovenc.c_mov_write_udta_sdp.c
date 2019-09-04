#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
struct TYPE_6__ {int /*<<< orphan*/ * streams; } ;
struct TYPE_5__ {int /*<<< orphan*/  track_id; int /*<<< orphan*/  src_track; TYPE_2__* rtp_ctx; } ;
typedef  TYPE_1__ MOVTrack ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_strlcatf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ff_sdp_write_media (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int mov_write_udta_sdp(AVIOContext *pb, MOVTrack *track)
{
    AVFormatContext *ctx = track->rtp_ctx;
    char buf[1000] = "";
    int len;

    ff_sdp_write_media(buf, sizeof(buf), ctx->streams[0], track->src_track,
                       NULL, NULL, 0, 0, ctx);
    av_strlcatf(buf, sizeof(buf), "a=control:streamid=%d\r\n", track->track_id);
    len = strlen(buf);

    avio_wb32(pb, len + 24);
    ffio_wfourcc(pb, "udta");
    avio_wb32(pb, len + 16);
    ffio_wfourcc(pb, "hnti");
    avio_wb32(pb, len + 8);
    ffio_wfourcc(pb, "sdp ");
    avio_write(pb, buf, len);
    return len + 24;
}