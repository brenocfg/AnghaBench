#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * pb; TYPE_1__* priv_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  counter; } ;
typedef  TYPE_1__ DSSDemuxContext ;
typedef  int /*<<< orphan*/  AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ DSS_AUDIO_BLOCK_HEADER_SIZE ; 
 scalar_t__ DSS_BLOCK_SIZE ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void dss_skip_audio_header(AVFormatContext *s, AVPacket *pkt)
{
    DSSDemuxContext *ctx = s->priv_data;
    AVIOContext *pb = s->pb;

    avio_skip(pb, DSS_AUDIO_BLOCK_HEADER_SIZE);
    ctx->counter += DSS_BLOCK_SIZE - DSS_AUDIO_BLOCK_HEADER_SIZE;
}