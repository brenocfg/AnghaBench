#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_10__ {TYPE_2__* priv_data; } ;
struct TYPE_9__ {scalar_t__ done; TYPE_1__* ctx; } ;
struct TYPE_8__ {int /*<<< orphan*/  pb; } ;
typedef  TYPE_2__ MatroskaDemuxContext ;
typedef  int /*<<< orphan*/  AVPacket ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ ) ; 
 scalar_t__ matroska_deliver_packet (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ matroska_parse_cluster (TYPE_2__*) ; 
 int matroska_resync (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int matroska_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    MatroskaDemuxContext *matroska = s->priv_data;
    int ret = 0;

    while (matroska_deliver_packet(matroska, pkt)) {
        int64_t pos = avio_tell(matroska->ctx->pb);
        if (matroska->done)
            return (ret < 0) ? ret : AVERROR_EOF;
        if (matroska_parse_cluster(matroska) < 0)
            ret = matroska_resync(matroska, pos);
    }

    return 0;
}