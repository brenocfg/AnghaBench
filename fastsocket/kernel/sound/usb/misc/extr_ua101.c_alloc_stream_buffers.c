#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ua101_stream {unsigned int queue_length; unsigned int max_packet_bytes; TYPE_2__* buffers; } ;
struct ua101 {TYPE_1__* dev; } ;
struct TYPE_4__ {size_t size; int /*<<< orphan*/  addr; int /*<<< orphan*/  dma; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_2__*) ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ MAX_QUEUE_LENGTH ; 
 scalar_t__ MIN_QUEUE_LENGTH ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 unsigned int max (unsigned int,unsigned int) ; 
 void* min (unsigned int,unsigned int) ; 
 unsigned int queue_length ; 
 int /*<<< orphan*/  usb_buffer_alloc (TYPE_1__*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int alloc_stream_buffers(struct ua101 *ua, struct ua101_stream *stream)
{
	unsigned int remaining_packets, packets, packets_per_page, i;
	size_t size;

	stream->queue_length = queue_length;
	stream->queue_length = max(stream->queue_length,
				   (unsigned int)MIN_QUEUE_LENGTH);
	stream->queue_length = min(stream->queue_length,
				   (unsigned int)MAX_QUEUE_LENGTH);

	/*
	 * The cache pool sizes used by usb_buffer_alloc() (128, 512, 2048) are
	 * quite bad when used with the packet sizes of this device (e.g. 280,
	 * 520, 624).  Therefore, we allocate and subdivide entire pages, using
	 * a smaller buffer only for the last chunk.
	 */
	remaining_packets = stream->queue_length;
	packets_per_page = PAGE_SIZE / stream->max_packet_bytes;
	for (i = 0; i < ARRAY_SIZE(stream->buffers); ++i) {
		packets = min(remaining_packets, packets_per_page);
		size = packets * stream->max_packet_bytes;
		stream->buffers[i].addr =
			usb_buffer_alloc(ua->dev, size, GFP_KERNEL,
					 &stream->buffers[i].dma);
		if (!stream->buffers[i].addr)
			return -ENOMEM;
		stream->buffers[i].size = size;
		remaining_packets -= packets;
		if (!remaining_packets)
			break;
	}
	if (remaining_packets) {
		dev_err(&ua->dev->dev, "too many packets\n");
		return -ENXIO;
	}
	return 0;
}