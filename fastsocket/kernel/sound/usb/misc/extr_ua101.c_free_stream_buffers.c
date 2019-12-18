#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ua101_stream {TYPE_1__* buffers; } ;
struct ua101 {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dma; int /*<<< orphan*/  addr; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_buffer_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_stream_buffers(struct ua101 *ua, struct ua101_stream *stream)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(stream->buffers); ++i)
		usb_buffer_free(ua->dev,
				stream->buffers[i].size,
				stream->buffers[i].addr,
				stream->buffers[i].dma);
}