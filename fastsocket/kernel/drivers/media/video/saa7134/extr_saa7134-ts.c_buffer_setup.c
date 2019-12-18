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
struct videobuf_queue {struct saa7134_dev* priv_data; } ;
struct TYPE_2__ {unsigned int nr_packets; unsigned int nr_bufs; } ;
struct saa7134_dev {TYPE_1__ ts; } ;

/* Variables and functions */
 unsigned int TS_PACKET_SIZE ; 
 unsigned int saa7134_buffer_count (unsigned int,unsigned int) ; 

__attribute__((used)) static int
buffer_setup(struct videobuf_queue *q, unsigned int *count, unsigned int *size)
{
	struct saa7134_dev *dev = q->priv_data;

	*size = TS_PACKET_SIZE * dev->ts.nr_packets;
	if (0 == *count)
		*count = dev->ts.nr_bufs;
	*count = saa7134_buffer_count(*size,*count);

	return 0;
}