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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct v4l2_subdev_io_pin_config {scalar_t__ strength; int pin; int flags; int value; int /*<<< orphan*/  function; } ;
struct v4l2_subdev {int dummy; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX23885_PAD_GPIO19 ; 
 int /*<<< orphan*/  CX23885_PAD_GPIO20 ; 
 int /*<<< orphan*/  CX23885_PAD_GPIO21 ; 
 int /*<<< orphan*/  CX23885_PAD_GPIO22 ; 
 int /*<<< orphan*/  CX23885_PAD_GPIO23 ; 
 int /*<<< orphan*/  CX23885_PAD_IRQ_N ; 
#define  CX23885_PIN_I2S_BCLK_GPIO23 133 
#define  CX23885_PIN_I2S_SDAT_GPIO21 132 
#define  CX23885_PIN_I2S_WCLK_GPIO22 131 
#define  CX23885_PIN_IRQ_N_GPIO16 130 
#define  CX23885_PIN_IR_RX_GPIO19 129 
#define  CX23885_PIN_IR_TX_GPIO20 128 
 scalar_t__ CX25840_PIN_DRIVE_FAST ; 
 int V4L2_SUBDEV_IO_PIN_ACTIVE_LOW ; 
 int V4L2_SUBDEV_IO_PIN_DISABLE ; 
 int V4L2_SUBDEV_IO_PIN_INPUT ; 
 int V4L2_SUBDEV_IO_PIN_SET_VALUE ; 
 scalar_t__ cx25840_read (struct i2c_client*,int) ; 
 int cx25840_read4 (struct i2c_client*,int) ; 
 int /*<<< orphan*/  cx25840_write (struct i2c_client*,int,scalar_t__) ; 
 int /*<<< orphan*/  cx25840_write4 (struct i2c_client*,int,int) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int cx23885_s_io_pin_config(struct v4l2_subdev *sd, size_t n,
				      struct v4l2_subdev_io_pin_config *p)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	int i;
	u32 pin_ctrl;
	u8 gpio_oe, gpio_data, strength;

	pin_ctrl = cx25840_read4(client, 0x120);
	gpio_oe = cx25840_read(client, 0x160);
	gpio_data = cx25840_read(client, 0x164);

	for (i = 0; i < n; i++) {
		strength = p[i].strength;
		if (strength > CX25840_PIN_DRIVE_FAST)
			strength = CX25840_PIN_DRIVE_FAST;

		switch (p[i].pin) {
		case CX23885_PIN_IRQ_N_GPIO16:
			if (p[i].function != CX23885_PAD_IRQ_N) {
				/* GPIO16 */
				pin_ctrl &= ~(0x1 << 25);
			} else {
				/* IRQ_N */
				if (p[i].flags &
					(V4L2_SUBDEV_IO_PIN_DISABLE |
					 V4L2_SUBDEV_IO_PIN_INPUT)) {
					pin_ctrl &= ~(0x1 << 25);
				} else {
					pin_ctrl |= (0x1 << 25);
				}
				if (p[i].flags &
					V4L2_SUBDEV_IO_PIN_ACTIVE_LOW) {
					pin_ctrl &= ~(0x1 << 24);
				} else {
					pin_ctrl |= (0x1 << 24);
				}
			}
			break;
		case CX23885_PIN_IR_RX_GPIO19:
			if (p[i].function != CX23885_PAD_GPIO19) {
				/* IR_RX */
				gpio_oe |= (0x1 << 0);
				pin_ctrl &= ~(0x3 << 18);
				pin_ctrl |= (strength << 18);
			} else {
				/* GPIO19 */
				gpio_oe &= ~(0x1 << 0);
				if (p[i].flags & V4L2_SUBDEV_IO_PIN_SET_VALUE) {
					gpio_data &= ~(0x1 << 0);
					gpio_data |= ((p[i].value & 0x1) << 0);
				}
				pin_ctrl &= ~(0x3 << 12);
				pin_ctrl |= (strength << 12);
			}
			break;
		case CX23885_PIN_IR_TX_GPIO20:
			if (p[i].function != CX23885_PAD_GPIO20) {
				/* IR_TX */
				gpio_oe |= (0x1 << 1);
				if (p[i].flags & V4L2_SUBDEV_IO_PIN_DISABLE)
					pin_ctrl &= ~(0x1 << 10);
				else
					pin_ctrl |= (0x1 << 10);
				pin_ctrl &= ~(0x3 << 18);
				pin_ctrl |= (strength << 18);
			} else {
				/* GPIO20 */
				gpio_oe &= ~(0x1 << 1);
				if (p[i].flags & V4L2_SUBDEV_IO_PIN_SET_VALUE) {
					gpio_data &= ~(0x1 << 1);
					gpio_data |= ((p[i].value & 0x1) << 1);
				}
				pin_ctrl &= ~(0x3 << 12);
				pin_ctrl |= (strength << 12);
			}
			break;
		case CX23885_PIN_I2S_SDAT_GPIO21:
			if (p[i].function != CX23885_PAD_GPIO21) {
				/* I2S_SDAT */
				/* TODO: Input or Output config */
				gpio_oe |= (0x1 << 2);
				pin_ctrl &= ~(0x3 << 22);
				pin_ctrl |= (strength << 22);
			} else {
				/* GPIO21 */
				gpio_oe &= ~(0x1 << 2);
				if (p[i].flags & V4L2_SUBDEV_IO_PIN_SET_VALUE) {
					gpio_data &= ~(0x1 << 2);
					gpio_data |= ((p[i].value & 0x1) << 2);
				}
				pin_ctrl &= ~(0x3 << 12);
				pin_ctrl |= (strength << 12);
			}
			break;
		case CX23885_PIN_I2S_WCLK_GPIO22:
			if (p[i].function != CX23885_PAD_GPIO22) {
				/* I2S_WCLK */
				/* TODO: Input or Output config */
				gpio_oe |= (0x1 << 3);
				pin_ctrl &= ~(0x3 << 22);
				pin_ctrl |= (strength << 22);
			} else {
				/* GPIO22 */
				gpio_oe &= ~(0x1 << 3);
				if (p[i].flags & V4L2_SUBDEV_IO_PIN_SET_VALUE) {
					gpio_data &= ~(0x1 << 3);
					gpio_data |= ((p[i].value & 0x1) << 3);
				}
				pin_ctrl &= ~(0x3 << 12);
				pin_ctrl |= (strength << 12);
			}
			break;
		case CX23885_PIN_I2S_BCLK_GPIO23:
			if (p[i].function != CX23885_PAD_GPIO23) {
				/* I2S_BCLK */
				/* TODO: Input or Output config */
				gpio_oe |= (0x1 << 4);
				pin_ctrl &= ~(0x3 << 22);
				pin_ctrl |= (strength << 22);
			} else {
				/* GPIO23 */
				gpio_oe &= ~(0x1 << 4);
				if (p[i].flags & V4L2_SUBDEV_IO_PIN_SET_VALUE) {
					gpio_data &= ~(0x1 << 4);
					gpio_data |= ((p[i].value & 0x1) << 4);
				}
				pin_ctrl &= ~(0x3 << 12);
				pin_ctrl |= (strength << 12);
			}
			break;
		}
	}

	cx25840_write(client, 0x164, gpio_data);
	cx25840_write(client, 0x160, gpio_oe);
	cx25840_write4(client, 0x120, pin_ctrl);
	return 0;
}