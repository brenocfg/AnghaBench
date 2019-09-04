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
struct TYPE_9__ {TYPE_1__* priv_data; } ;
struct TYPE_8__ {int* data; } ;
struct TYPE_7__ {int pkt_offset; int /*<<< orphan*/  data_type; } ;
typedef  TYPE_1__ IEC61937Context ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  IEC61937_MPEG2_EXT ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ ** mpeg_data_type ; 
 int** spdif_mpeg_pkt_offset ; 

__attribute__((used)) static int spdif_header_mpeg(AVFormatContext *s, AVPacket *pkt)
{
    IEC61937Context *ctx = s->priv_data;
    int version =      (pkt->data[1] >> 3) & 3;
    int layer   = 3 - ((pkt->data[1] >> 1) & 3);
    int extension = pkt->data[2] & 1;

    if (layer == 3 || version == 1) {
        av_log(s, AV_LOG_ERROR, "Wrong MPEG file format\n");
        return AVERROR_INVALIDDATA;
    }
    av_log(s, AV_LOG_DEBUG, "version: %i layer: %i extension: %i\n", version, layer, extension);
    if (version == 2 && extension) {
        ctx->data_type  = IEC61937_MPEG2_EXT;
        ctx->pkt_offset = 4608;
    } else {
        ctx->data_type  = mpeg_data_type [version & 1][layer];
        ctx->pkt_offset = spdif_mpeg_pkt_offset[version & 1][layer];
    }
    // TODO Data type dependent info (normal/karaoke, dynamic range control)
    return 0;
}