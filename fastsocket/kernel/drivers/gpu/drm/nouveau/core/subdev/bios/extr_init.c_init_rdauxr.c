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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct nvbios_init {int dummy; } ;
struct nouveau_i2c_port {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ init_exec (struct nvbios_init*) ; 
 struct nouveau_i2c_port* init_i2c (struct nvbios_init*,int) ; 
 int nv_rdaux (struct nouveau_i2c_port*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int
init_rdauxr(struct nvbios_init *init, u32 addr)
{
	struct nouveau_i2c_port *port = init_i2c(init, -2);
	u8 data;

	if (port && init_exec(init)) {
		int ret = nv_rdaux(port, addr, &data, 1);
		if (ret)
			return ret;
		return data;
	}

	return -ENODEV;
}