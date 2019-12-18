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
typedef  enum AVPacketSideDataType { ____Placeholder_AVPacketSideDataType } AVPacketSideDataType ;
typedef  int /*<<< orphan*/  AVPacket ;

/* Variables and functions */
 unsigned int AV_INPUT_BUFFER_PADDING_SIZE ; 
 unsigned int INT_MAX ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * av_mallocz (unsigned int) ; 
 int av_packet_add_side_data (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 

uint8_t *av_packet_new_side_data(AVPacket *pkt, enum AVPacketSideDataType type,
                                 int size)
{
    int ret;
    uint8_t *data;

    if ((unsigned)size > INT_MAX - AV_INPUT_BUFFER_PADDING_SIZE)
        return NULL;
    data = av_mallocz(size + AV_INPUT_BUFFER_PADDING_SIZE);
    if (!data)
        return NULL;

    ret = av_packet_add_side_data(pkt, type, data, size);
    if (ret < 0) {
        av_freep(&data);
        return NULL;
    }

    return data;
}