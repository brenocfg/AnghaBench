#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_12__ {size_t stream_index; } ;
struct TYPE_9__ {TYPE_2__* elem; } ;
struct TYPE_11__ {int /*<<< orphan*/  ctx; int /*<<< orphan*/  queue_end; scalar_t__ queue; TYPE_1__ tracks; } ;
struct TYPE_10__ {scalar_t__ has_palette; int /*<<< orphan*/  palette; } ;
typedef  TYPE_2__ MatroskaTrack ;
typedef  TYPE_3__ MatroskaDemuxContext ;
typedef  TYPE_4__ AVPacket ;

/* Variables and functions */
 int /*<<< orphan*/  AVPALETTE_SIZE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PKT_DATA_PALETTE ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * av_packet_new_side_data (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_packet_list_get (scalar_t__*,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int matroska_deliver_packet(MatroskaDemuxContext *matroska,
                                   AVPacket *pkt)
{
    if (matroska->queue) {
        MatroskaTrack *tracks = matroska->tracks.elem;
        MatroskaTrack *track;

        ff_packet_list_get(&matroska->queue, &matroska->queue_end, pkt);
        track = &tracks[pkt->stream_index];
        if (track->has_palette) {
            uint8_t *pal = av_packet_new_side_data(pkt, AV_PKT_DATA_PALETTE, AVPALETTE_SIZE);
            if (!pal) {
                av_log(matroska->ctx, AV_LOG_ERROR, "Cannot append palette to packet\n");
            } else {
                memcpy(pal, track->palette, AVPALETTE_SIZE);
            }
            track->has_palette = 0;
        }
        return 0;
    }

    return -1;
}