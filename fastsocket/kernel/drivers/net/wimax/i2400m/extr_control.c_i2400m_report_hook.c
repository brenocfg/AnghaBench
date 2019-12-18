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

/* Variables and functions */
 int /*<<< orphan*/  I2400M_MS_DONE_OK ; 
#define  I2400M_MT_REPORT_POWERSAVE_READY 129 
#define  I2400M_MT_REPORT_STATE 128 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_fnend (int,struct device*,char*,struct i2400m*,struct i2400m_l3l4_hdr const*,size_t) ; 
 int /*<<< orphan*/  d_fnstart (int,struct device*,char*,struct i2400m*,struct i2400m_l3l4_hdr const*,size_t) ; 
 int /*<<< orphan*/  d_printf (int,struct device*,char*) ; 
 int /*<<< orphan*/  i2400m_cmd_enter_powersave (struct i2400m*) ; 
 struct device* i2400m_dev (struct i2400m*) ; 
 int /*<<< orphan*/  i2400m_power_save_disabled ; 
 int /*<<< orphan*/  i2400m_report_state_hook (struct i2400m*,struct i2400m_l3l4_hdr const*,size_t,char*) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 

void i2400m_report_hook(struct i2400m *i2400m,
			const struct i2400m_l3l4_hdr *l3l4_hdr, size_t size)
{
	struct device *dev = i2400m_dev(i2400m);
	unsigned msg_type;

	d_fnstart(3, dev, "(i2400m %p l3l4_hdr %p size %zu)\n",
		  i2400m, l3l4_hdr, size);
	/* Chew on the message, we might need some information from
	 * here */
	msg_type = le16_to_cpu(l3l4_hdr->type);
	switch (msg_type) {
	case I2400M_MT_REPORT_STATE:	/* carrier detection... */
		i2400m_report_state_hook(i2400m,
					 l3l4_hdr, size, "REPORT STATE");
		break;
	/* If the device is ready for power save, then ask it to do
	 * it. */
	case I2400M_MT_REPORT_POWERSAVE_READY:	/* zzzzz */
		if (l3l4_hdr->status == cpu_to_le16(I2400M_MS_DONE_OK)) {
			if (i2400m_power_save_disabled)
				d_printf(1, dev, "ready for powersave, "
					 "not requesting (disabled by module "
					 "parameter)\n");
			else {
				d_printf(1, dev, "ready for powersave, "
					 "requesting\n");
				i2400m_cmd_enter_powersave(i2400m);
			}
		}
		break;
	};
	d_fnend(3, dev, "(i2400m %p l3l4_hdr %p size %zu) = void\n",
		i2400m, l3l4_hdr, size);
}