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
struct smd_channel {TYPE_1__* send; } ;
struct TYPE_2__ {unsigned int head; unsigned int tail; scalar_t__ data; } ;

/* Variables and functions */
 unsigned int SMD_BUF_SIZE ; 

__attribute__((used)) static unsigned ch_write_buffer(struct smd_channel *ch, void **ptr)
{
	unsigned head = ch->send->head;
	unsigned tail = ch->send->tail;
	*ptr = (void *) (ch->send->data + head);

	if (head < tail) {
		return tail - head - 1;
	} else {
		if (tail == 0)
			return SMD_BUF_SIZE - head - 1;
		else
			return SMD_BUF_SIZE - head;
	}
}