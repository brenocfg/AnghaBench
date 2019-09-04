#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int size; int /*<<< orphan*/ * data; int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ AVPacket ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int INT_MAX ; 
 int /*<<< orphan*/  av_buffer_create (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_buffer_default_free ; 

int av_packet_from_data(AVPacket *pkt, uint8_t *data, int size)
{
    if (size >= INT_MAX - AV_INPUT_BUFFER_PADDING_SIZE)
        return AVERROR(EINVAL);

    pkt->buf = av_buffer_create(data, size + AV_INPUT_BUFFER_PADDING_SIZE,
                                av_buffer_default_free, NULL, 0);
    if (!pkt->buf)
        return AVERROR(ENOMEM);

    pkt->data = data;
    pkt->size = size;

    return 0;
}