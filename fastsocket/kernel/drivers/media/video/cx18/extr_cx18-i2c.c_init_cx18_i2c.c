#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct i2c_algo_bit_data {int dummy; } ;
struct i2c_adapter {int dummy; } ;
struct cx18 {int instance; TYPE_3__* i2c_adap; TYPE_7__* i2c_algo_cb_data; TYPE_2__* pci_dev; int /*<<< orphan*/  v4l2_dev; TYPE_3__* i2c_algo; } ;
struct TYPE_12__ {int bus_index; struct cx18* cx; } ;
struct TYPE_9__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_11__ {TYPE_1__ dev; scalar_t__ name; struct TYPE_11__* algo_data; TYPE_7__* data; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX18_DEBUG_I2C (char*) ; 
 scalar_t__ CX18_GPIO_RESET_I2C ; 
 int /*<<< orphan*/  CX18_HW_GPIO_RESET_CTRL ; 
 int CX18_REG_I2C_1_WR ; 
 int CX18_REG_I2C_2_WR ; 
 int HW2_I2C1_INT ; 
 int HW2_I2C2_INT ; 
 int HW2_INT_CLR_STATUS ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  cx18_call_hw (struct cx18*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx18_i2c_adap_template ; 
 int /*<<< orphan*/  cx18_i2c_algo_template ; 
 int cx18_read_reg (struct cx18*,int) ; 
 int /*<<< orphan*/  cx18_setscl (TYPE_7__*,int) ; 
 int /*<<< orphan*/  cx18_setsda (TYPE_7__*,int) ; 
 int /*<<< orphan*/  cx18_write_reg (struct cx18*,int,int) ; 
 int /*<<< orphan*/  cx18_write_reg_expect (struct cx18*,int,int,int,int) ; 
 int i2c_bit_add_bus (TYPE_3__*) ; 
 int /*<<< orphan*/  i2c_del_adapter (TYPE_3__*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  reset ; 
 int /*<<< orphan*/  sprintf (scalar_t__,char*,int,int) ; 
 scalar_t__ strlen (scalar_t__) ; 

int init_cx18_i2c(struct cx18 *cx)
{
	int i, err;
	CX18_DEBUG_I2C("i2c init\n");

	for (i = 0; i < 2; i++) {
		/* Setup algorithm for adapter */
		memcpy(&cx->i2c_algo[i], &cx18_i2c_algo_template,
			sizeof(struct i2c_algo_bit_data));
		cx->i2c_algo_cb_data[i].cx = cx;
		cx->i2c_algo_cb_data[i].bus_index = i;
		cx->i2c_algo[i].data = &cx->i2c_algo_cb_data[i];

		/* Setup adapter */
		memcpy(&cx->i2c_adap[i], &cx18_i2c_adap_template,
			sizeof(struct i2c_adapter));
		cx->i2c_adap[i].algo_data = &cx->i2c_algo[i];
		sprintf(cx->i2c_adap[i].name + strlen(cx->i2c_adap[i].name),
				" #%d-%d", cx->instance, i);
		i2c_set_adapdata(&cx->i2c_adap[i], &cx->v4l2_dev);
		cx->i2c_adap[i].dev.parent = &cx->pci_dev->dev;
	}

	if (cx18_read_reg(cx, CX18_REG_I2C_2_WR) != 0x0003c02f) {
		/* Reset/Unreset I2C hardware block */
		/* Clock select 220MHz */
		cx18_write_reg_expect(cx, 0x10000000, 0xc71004,
					  0x00000000, 0x10001000);
		/* Clock Enable */
		cx18_write_reg_expect(cx, 0x10001000, 0xc71024,
					  0x00001000, 0x10001000);
	}
	/* courtesy of Steven Toth <stoth@hauppauge.com> */
	cx18_write_reg_expect(cx, 0x00c00000, 0xc7001c, 0x00000000, 0x00c000c0);
	mdelay(10);
	cx18_write_reg_expect(cx, 0x00c000c0, 0xc7001c, 0x000000c0, 0x00c000c0);
	mdelay(10);
	cx18_write_reg_expect(cx, 0x00c00000, 0xc7001c, 0x00000000, 0x00c000c0);
	mdelay(10);

	/* Set to edge-triggered intrs. */
	cx18_write_reg(cx, 0x00c00000, 0xc730c8);
	/* Clear any stale intrs */
	cx18_write_reg_expect(cx, HW2_I2C1_INT|HW2_I2C2_INT, HW2_INT_CLR_STATUS,
		       ~(HW2_I2C1_INT|HW2_I2C2_INT), HW2_I2C1_INT|HW2_I2C2_INT);

	/* Hw I2C1 Clock Freq ~100kHz */
	cx18_write_reg(cx, 0x00021c0f & ~4, CX18_REG_I2C_1_WR);
	cx18_setscl(&cx->i2c_algo_cb_data[0], 1);
	cx18_setsda(&cx->i2c_algo_cb_data[0], 1);

	/* Hw I2C2 Clock Freq ~100kHz */
	cx18_write_reg(cx, 0x00021c0f & ~4, CX18_REG_I2C_2_WR);
	cx18_setscl(&cx->i2c_algo_cb_data[1], 1);
	cx18_setsda(&cx->i2c_algo_cb_data[1], 1);

	cx18_call_hw(cx, CX18_HW_GPIO_RESET_CTRL,
		     core, reset, (u32) CX18_GPIO_RESET_I2C);

	err = i2c_bit_add_bus(&cx->i2c_adap[0]);
	if (err)
		goto err;
	err = i2c_bit_add_bus(&cx->i2c_adap[1]);
	if (err)
		goto err_del_bus_0;
	return 0;

 err_del_bus_0:
	i2c_del_adapter(&cx->i2c_adap[0]);
 err:
	return err;
}