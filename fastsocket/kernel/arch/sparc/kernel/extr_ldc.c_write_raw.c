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
struct ldc_packet {int dummy; } ;
struct ldc_channel {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EMSGSIZE ; 
 unsigned int LDC_PACKET_SIZE ; 
 struct ldc_packet* data_get_tx_packet (struct ldc_channel*,unsigned long*) ; 
 int /*<<< orphan*/  memcpy (struct ldc_packet*,void const*,unsigned int) ; 
 int send_tx_packet (struct ldc_channel*,struct ldc_packet*,unsigned long) ; 

__attribute__((used)) static int write_raw(struct ldc_channel *lp, const void *buf, unsigned int size)
{
	struct ldc_packet *p;
	unsigned long new_tail;
	int err;

	if (size > LDC_PACKET_SIZE)
		return -EMSGSIZE;

	p = data_get_tx_packet(lp, &new_tail);
	if (!p)
		return -EAGAIN;

	memcpy(p, buf, size);

	err = send_tx_packet(lp, p, new_tail);
	if (!err)
		err = size;

	return err;
}