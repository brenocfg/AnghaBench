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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/ * func; } ;
struct nv4e_i2c_port {scalar_t__ addr; TYPE_1__ base; } ;
struct nouveau_oclass {int dummy; } ;
struct nouveau_object {int dummy; } ;
struct dcb_i2c_entry {scalar_t__ drive; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_i2c_bit_algo ; 
 int nouveau_i2c_port_create (struct nouveau_object*,struct nouveau_object*,struct nouveau_oclass*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct nv4e_i2c_port**) ; 
 int /*<<< orphan*/  nv4e_i2c_func ; 
 struct nouveau_object* nv_object (struct nv4e_i2c_port*) ; 

__attribute__((used)) static int
nv4e_i2c_port_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
		   struct nouveau_oclass *oclass, void *data, u32 index,
		   struct nouveau_object **pobject)
{
	struct dcb_i2c_entry *info = data;
	struct nv4e_i2c_port *port;
	int ret;

	ret = nouveau_i2c_port_create(parent, engine, oclass, index,
				     &nouveau_i2c_bit_algo, &port);
	*pobject = nv_object(port);
	if (ret)
		return ret;

	port->base.func = &nv4e_i2c_func;
	port->addr = 0x600800 + info->drive;
	return 0;
}