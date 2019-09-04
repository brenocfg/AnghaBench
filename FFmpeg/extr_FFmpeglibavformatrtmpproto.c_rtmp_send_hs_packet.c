#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  stream; } ;
typedef  TYPE_1__ RTMPContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_WB32 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EIO ; 
 int RTMP_HANDSHAKE_PACKET_SIZE ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int ffurl_write (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int rtmp_send_hs_packet(RTMPContext* rt, uint32_t first_int,
                               uint32_t second_int, char *arraydata, int size)
{
    int inoutsize;

    AV_WB32(arraydata, first_int);
    AV_WB32(arraydata + 4, second_int);
    inoutsize = ffurl_write(rt->stream, arraydata,
                            RTMP_HANDSHAKE_PACKET_SIZE);
    if (inoutsize != RTMP_HANDSHAKE_PACKET_SIZE) {
        av_log(rt, AV_LOG_ERROR, "Unable to write answer\n");
        return AVERROR(EIO);
    }

    return 0;
}