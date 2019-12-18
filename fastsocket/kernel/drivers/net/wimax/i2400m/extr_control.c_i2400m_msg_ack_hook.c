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
struct i2400m_l3l4_hdr {int /*<<< orphan*/  status; int /*<<< orphan*/  type; } ;
struct i2400m {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  strerr ;

/* Variables and functions */
#define  I2400M_MT_CMD_ENTER_POWERSAVE 128 
 int /*<<< orphan*/  d_printf (int,struct device*,char*,size_t) ; 
 struct device* i2400m_dev (struct i2400m*) ; 
 int i2400m_msg_check_status (struct i2400m_l3l4_hdr const*,char*,int) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 

void i2400m_msg_ack_hook(struct i2400m *i2400m,
			 const struct i2400m_l3l4_hdr *l3l4_hdr, size_t size)
{
	int result;
	struct device *dev = i2400m_dev(i2400m);
	unsigned ack_type, ack_status;
	char strerr[32];

	/* Chew on the message, we might need some information from
	 * here */
	ack_type = le16_to_cpu(l3l4_hdr->type);
	ack_status = le16_to_cpu(l3l4_hdr->status);
	switch (ack_type) {
	case I2400M_MT_CMD_ENTER_POWERSAVE:
		/* This is just left here for the sake of example, as
		 * the processing is done somewhere else. */
		if (0) {
			result = i2400m_msg_check_status(
				l3l4_hdr, strerr, sizeof(strerr));
			if (result >= 0)
				d_printf(1, dev, "ready for power save: %zd\n",
					 size);
		}
		break;
	};
	return;
}