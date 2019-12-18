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
typedef  int u8 ;
typedef  int u32 ;
struct nouveau_i2c_port {int dummy; } ;
struct anx9805_i2c_port {int /*<<< orphan*/  ctrl; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {scalar_t__ parent; } ;

/* Variables and functions */
 int EIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  mdelay (int) ; 
 TYPE_1__* nv_object (struct anx9805_i2c_port*) ; 
 int nv_rdi2cr (struct nouveau_i2c_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nv_wri2cr (struct nouveau_i2c_port*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
anx9805_aux(struct nouveau_i2c_port *port, u8 type, u32 addr, u8 *data, u8 size)
{
	struct anx9805_i2c_port *chan = (void *)port;
	struct nouveau_i2c_port *mast = (void *)nv_object(chan)->parent;
	int i, ret = -ETIMEDOUT;
	u8 tmp;

	tmp = nv_rdi2cr(mast, chan->ctrl, 0x07) & ~0x04;
	nv_wri2cr(mast, chan->ctrl, 0x07, tmp | 0x04);
	nv_wri2cr(mast, chan->ctrl, 0x07, tmp);
	nv_wri2cr(mast, chan->ctrl, 0xf7, 0x01);

	nv_wri2cr(mast, chan->addr, 0xe4, 0x80);
	for (i = 0; !(type & 1) && i < size; i++)
		nv_wri2cr(mast, chan->addr, 0xf0 + i, data[i]);
	nv_wri2cr(mast, chan->addr, 0xe5, ((size - 1) << 4) | type);
	nv_wri2cr(mast, chan->addr, 0xe6, (addr & 0x000ff) >>  0);
	nv_wri2cr(mast, chan->addr, 0xe7, (addr & 0x0ff00) >>  8);
	nv_wri2cr(mast, chan->addr, 0xe8, (addr & 0xf0000) >> 16);
	nv_wri2cr(mast, chan->addr, 0xe9, 0x01);

	i = 0;
	while ((tmp = nv_rdi2cr(mast, chan->addr, 0xe9)) & 0x01) {
		mdelay(5);
		if (i++ == 32)
			goto done;
	}

	if ((tmp = nv_rdi2cr(mast, chan->ctrl, 0xf7)) & 0x01) {
		ret = -EIO;
		goto done;
	}

	for (i = 0; (type & 1) && i < size; i++)
		data[i] = nv_rdi2cr(mast, chan->addr, 0xf0 + i);
	ret = 0;
done:
	nv_wri2cr(mast, chan->ctrl, 0xf7, 0x01);
	return ret;
}