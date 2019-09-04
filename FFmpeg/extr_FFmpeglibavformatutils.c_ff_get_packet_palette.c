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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int data; int size; } ;
typedef  TYPE_1__ AVPacket ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AVPALETTE_COUNT ; 
 int AVPALETTE_SIZE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PKT_DATA_PALETTE ; 
 int /*<<< orphan*/  AV_RL32 (int) ; 
 int CONTAINS_PAL ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * av_packet_get_side_data (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int ff_get_packet_palette(AVFormatContext *s, AVPacket *pkt, int ret, uint32_t *palette)
{
    uint8_t *side_data;
    int size;

    side_data = av_packet_get_side_data(pkt, AV_PKT_DATA_PALETTE, &size);
    if (side_data) {
        if (size != AVPALETTE_SIZE) {
            av_log(s, AV_LOG_ERROR, "Invalid palette side data\n");
            return AVERROR_INVALIDDATA;
        }
        memcpy(palette, side_data, AVPALETTE_SIZE);
        return 1;
    }

    if (ret == CONTAINS_PAL) {
        int i;
        for (i = 0; i < AVPALETTE_COUNT; i++)
            palette[i] = AV_RL32(pkt->data + pkt->size - AVPALETTE_SIZE + i*4);
        return 1;
    }

    return 0;
}