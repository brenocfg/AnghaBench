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
typedef  size_t u8 ;
struct nvbios_init {scalar_t__ offset; struct nouveau_bios* bios; } ;
struct nouveau_i2c_port {int /*<<< orphan*/  adapter; } ;
struct nouveau_bios {int dummy; } ;
struct i2c_msg {size_t addr; size_t len; size_t* buf; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int i2c_transfer (int /*<<< orphan*/ *,struct i2c_msg*,int) ; 
 scalar_t__ init_exec (struct nvbios_init*) ; 
 struct nouveau_i2c_port* init_i2c (struct nvbios_init*,size_t) ; 
 int nv_ro08 (struct nouveau_bios*,scalar_t__) ; 
 int /*<<< orphan*/  trace (char*,size_t,...) ; 
 int /*<<< orphan*/  warn (char*,int) ; 

__attribute__((used)) static void
init_zm_i2c(struct nvbios_init *init)
{
	struct nouveau_bios *bios = init->bios;
	u8 index = nv_ro08(bios, init->offset + 1);
	u8  addr = nv_ro08(bios, init->offset + 2) >> 1;
	u8 count = nv_ro08(bios, init->offset + 3);
	u8 data[256], i;

	trace("ZM_I2C\tI2C[0x%02x][0x%02x]\n", index, addr);
	init->offset += 4;

	for (i = 0; i < count; i++) {
		data[i] = nv_ro08(bios, init->offset);
		trace("\t0x%02x\n", data[i]);
		init->offset++;
	}

	if (init_exec(init)) {
		struct nouveau_i2c_port *port = init_i2c(init, index);
		struct i2c_msg msg = {
			.addr = addr, .flags = 0, .len = count, .buf = data,
		};
		int ret;

		if (port && (ret = i2c_transfer(&port->adapter, &msg, 1)) != 1)
			warn("i2c wr failed, %d\n", ret);
	}
}