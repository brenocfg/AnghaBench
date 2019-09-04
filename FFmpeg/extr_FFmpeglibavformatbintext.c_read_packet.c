#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  pb; TYPE_1__* priv_data; } ;
struct TYPE_8__ {int /*<<< orphan*/  flags; } ;
struct TYPE_7__ {int fsize; int chars_per_frame; } ;
typedef  TYPE_1__ BinDemuxContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  EIO ; 
 scalar_t__ av_get_packet (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 scalar_t__ avio_feof (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_packet(AVFormatContext *s,
                           AVPacket *pkt)
{
    BinDemuxContext *bin = s->priv_data;

    if (bin->fsize > 0) {
        if (av_get_packet(s->pb, pkt, bin->fsize) < 0)
            return AVERROR(EIO);
        bin->fsize = -1; /* done */
    } else if (!bin->fsize) {
        if (avio_feof(s->pb))
            return AVERROR(EIO);
        if (av_get_packet(s->pb, pkt, bin->chars_per_frame) < 0)
            return AVERROR(EIO);
    } else {
        return AVERROR(EIO);
    }

    pkt->flags |= AV_PKT_FLAG_KEY;
    return 0;
}