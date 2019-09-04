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
struct TYPE_7__ {TYPE_1__* priv_data; } ;
struct TYPE_6__ {scalar_t__ audio_codec; } ;
typedef  TYPE_1__ DSSDemuxContext ;
typedef  int /*<<< orphan*/  AVPacket ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ DSS_ACODEC_DSS_SP ; 
 int dss_723_1_read_packet (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int dss_sp_read_packet (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dss_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    DSSDemuxContext *ctx = s->priv_data;

    if (ctx->audio_codec == DSS_ACODEC_DSS_SP)
        return dss_sp_read_packet(s, pkt);
    else
        return dss_723_1_read_packet(s, pkt);
}