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
struct vp3054_i2c_state {int state; } ;
struct cx88_core {int dummy; } ;
struct cx8802_dev {struct vp3054_i2c_state* vp3054; struct cx88_core* core; } ;

/* Variables and functions */
 int /*<<< orphan*/  MO_GP0_IO ; 
 int /*<<< orphan*/  cx_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vp3054_bit_setscl(void *data, int state)
{
	struct cx8802_dev *dev = data;
	struct cx88_core *core = dev->core;
	struct vp3054_i2c_state *vp3054_i2c = dev->vp3054;

	if (state) {
		vp3054_i2c->state |=  0x0001;	/* SCL high */
		vp3054_i2c->state &= ~0x0100;	/* external pullup */
	} else {
		vp3054_i2c->state &= ~0x0001;	/* SCL low */
		vp3054_i2c->state |=  0x0100;	/* drive pin */
	}
	cx_write(MO_GP0_IO, 0x010000 | vp3054_i2c->state);
	cx_read(MO_GP0_IO);
}