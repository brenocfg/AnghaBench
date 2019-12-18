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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct s6i2c_if {size_t msgs_done; size_t msgs_num; size_t msgs_push; size_t push; size_t done; int /*<<< orphan*/  complete; struct i2c_msg* msgs; TYPE_1__ adap; } ;
struct i2c_msg {int flags; int* buf; size_t len; } ;

/* Variables and functions */
 int I2C_M_RD ; 
 int /*<<< orphan*/  S6_I2C_CLRTXABRT ; 
 int /*<<< orphan*/  S6_I2C_DATACMD ; 
 int S6_I2C_DATACMD_READ ; 
 int /*<<< orphan*/  S6_I2C_INTRMASK ; 
 int /*<<< orphan*/  S6_I2C_INTRSTAT ; 
 int S6_I2C_INTR_RXFULL ; 
 int S6_I2C_INTR_TXABRT ; 
 int S6_I2C_INTR_TXEMPTY ; 
 int /*<<< orphan*/  S6_I2C_STATUS ; 
 int S6_I2C_STATUS_RFNE ; 
 int S6_I2C_STATUS_TFNF ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int i2c_rd16 (struct s6i2c_if*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_wr16 (struct s6i2c_if*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void s6i2c_handle_interrupt(struct s6i2c_if *iface)
{
	if (i2c_rd16(iface, S6_I2C_INTRSTAT) & (1 << S6_I2C_INTR_TXABRT)) {
		i2c_rd16(iface, S6_I2C_CLRTXABRT);
		i2c_wr16(iface, S6_I2C_INTRMASK, 0);
		complete(&iface->complete);
		return;
	}
	if (iface->msgs_done >= iface->msgs_num) {
		dev_err(&iface->adap.dev, "s6i2c: spurious I2C irq: %04x\n",
			i2c_rd16(iface, S6_I2C_INTRSTAT));
		i2c_wr16(iface, S6_I2C_INTRMASK, 0);
		return;
	}
	while ((iface->msgs_push < iface->msgs_num)
	    && (i2c_rd16(iface, S6_I2C_STATUS) & (1 << S6_I2C_STATUS_TFNF))) {
		struct i2c_msg *m = &iface->msgs[iface->msgs_push];
		if (!(m->flags & I2C_M_RD))
			i2c_wr16(iface, S6_I2C_DATACMD, m->buf[iface->push]);
		else
			i2c_wr16(iface, S6_I2C_DATACMD,
				 1 << S6_I2C_DATACMD_READ);
		if (++iface->push >= m->len) {
			iface->push = 0;
			iface->msgs_push += 1;
		}
	}
	do {
		struct i2c_msg *m = &iface->msgs[iface->msgs_done];
		if (!(m->flags & I2C_M_RD)) {
			if (iface->msgs_done < iface->msgs_push)
				iface->msgs_done += 1;
			else
				break;
		} else if (i2c_rd16(iface, S6_I2C_STATUS)
				& (1 << S6_I2C_STATUS_RFNE)) {
			m->buf[iface->done] = i2c_rd16(iface, S6_I2C_DATACMD);
			if (++iface->done >= m->len) {
				iface->done = 0;
				iface->msgs_done += 1;
			}
		} else{
			break;
		}
	} while (iface->msgs_done < iface->msgs_num);
	if (iface->msgs_done >= iface->msgs_num) {
		i2c_wr16(iface, S6_I2C_INTRMASK, 1 << S6_I2C_INTR_TXABRT);
		complete(&iface->complete);
	} else if (iface->msgs_push >= iface->msgs_num) {
		i2c_wr16(iface, S6_I2C_INTRMASK, (1 << S6_I2C_INTR_TXABRT) |
						 (1 << S6_I2C_INTR_RXFULL));
	} else {
		i2c_wr16(iface, S6_I2C_INTRMASK, (1 << S6_I2C_INTR_TXABRT) |
						 (1 << S6_I2C_INTR_TXEMPTY) |
						 (1 << S6_I2C_INTR_RXFULL));
	}
}