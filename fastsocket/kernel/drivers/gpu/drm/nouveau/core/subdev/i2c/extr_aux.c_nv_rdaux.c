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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct nouveau_i2c_port {TYPE_1__* func; } ;
struct TYPE_2__ {int (* aux ) (struct nouveau_i2c_port*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* acquire ) (struct nouveau_i2c_port*) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  stub1 (struct nouveau_i2c_port*) ; 
 int stub2 (struct nouveau_i2c_port*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
nv_rdaux(struct nouveau_i2c_port *port, u32 addr, u8 *data, u8 size)
{
	if (port->func->aux) {
		if (port->func->acquire)
			port->func->acquire(port);
		return port->func->aux(port, 9, addr, data, size);
	}
	return -ENODEV;
}