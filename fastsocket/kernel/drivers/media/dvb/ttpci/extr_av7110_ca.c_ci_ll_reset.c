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
typedef  int u8 ;
struct file {int dummy; } ;
struct dvb_ringbuffer {int dummy; } ;
struct TYPE_3__ {scalar_t__ flags; } ;
typedef  TYPE_1__ ca_slot_info_t ;

/* Variables and functions */
 int EBUSY ; 
 int dvb_ringbuffer_free (struct dvb_ringbuffer*) ; 
 int /*<<< orphan*/  dvb_ringbuffer_write (struct dvb_ringbuffer*,int*,int) ; 

__attribute__((used)) static int ci_ll_reset(struct dvb_ringbuffer *cibuf, struct file *file,
		       int slots, ca_slot_info_t *slot)
{
	int i;
	int len = 0;
	u8 msg[8] = { 0x00, 0x06, 0x00, 0x00, 0xff, 0x02, 0x00, 0x00 };

	for (i = 0; i < 2; i++) {
		if (slots & (1 << i))
			len += 8;
	}

	if (dvb_ringbuffer_free(cibuf) < len)
		return -EBUSY;

	for (i = 0; i < 2; i++) {
		if (slots & (1 << i)) {
			msg[2] = i;
			dvb_ringbuffer_write(cibuf, msg, 8);
			slot[i].flags = 0;
		}
	}

	return 0;
}