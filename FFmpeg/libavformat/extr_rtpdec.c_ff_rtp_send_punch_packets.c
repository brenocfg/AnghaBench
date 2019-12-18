#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  URLContext ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int RTCP_RR ; 
 int RTP_VERSION ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 
 int avio_close_dyn_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  avio_flush (int /*<<< orphan*/ *) ; 
 scalar_t__ avio_open_dyn_buf (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffurl_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void ff_rtp_send_punch_packets(URLContext *rtp_handle)
{
    AVIOContext *pb;
    uint8_t *buf;
    int len;

    /* Send a small RTP packet */
    if (avio_open_dyn_buf(&pb) < 0)
        return;

    avio_w8(pb, (RTP_VERSION << 6));
    avio_w8(pb, 0); /* Payload type */
    avio_wb16(pb, 0); /* Seq */
    avio_wb32(pb, 0); /* Timestamp */
    avio_wb32(pb, 0); /* SSRC */

    avio_flush(pb);
    len = avio_close_dyn_buf(pb, &buf);
    if ((len > 0) && buf)
        ffurl_write(rtp_handle, buf, len);
    av_free(buf);

    /* Send a minimal RTCP RR */
    if (avio_open_dyn_buf(&pb) < 0)
        return;

    avio_w8(pb, (RTP_VERSION << 6));
    avio_w8(pb, RTCP_RR); /* receiver report */
    avio_wb16(pb, 1); /* length in words - 1 */
    avio_wb32(pb, 0); /* our own SSRC */

    avio_flush(pb);
    len = avio_close_dyn_buf(pb, &buf);
    if ((len > 0) && buf)
        ffurl_write(rtp_handle, buf, len);
    av_free(buf);
}