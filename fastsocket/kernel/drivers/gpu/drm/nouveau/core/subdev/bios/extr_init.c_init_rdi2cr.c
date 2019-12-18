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
typedef  int /*<<< orphan*/  u8 ;
struct nvbios_init {int dummy; } ;
struct nouveau_i2c_port {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ init_exec (struct nvbios_init*) ; 
 struct nouveau_i2c_port* init_i2c (struct nvbios_init*,int /*<<< orphan*/ ) ; 
 int nv_rdi2cr (struct nouveau_i2c_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
init_rdi2cr(struct nvbios_init *init, u8 index, u8 addr, u8 reg)
{
	struct nouveau_i2c_port *port = init_i2c(init, index);
	if (port && init_exec(init))
		return nv_rdi2cr(port, addr, reg);
	return -ENODEV;
}