#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct nouveau_oclass {int handle; } ;
struct nouveau_object {int dummy; } ;
struct TYPE_3__ {struct i2c_algo_bit_data* algo_data; int /*<<< orphan*/ * algo; } ;
struct nouveau_i2c_port {TYPE_1__ adapter; } ;
struct i2c_algo_bit_data {int /*<<< orphan*/  udelay; } ;
struct TYPE_4__ {int /*<<< orphan*/ * func; } ;
struct anx9805_i2c_port {int addr; int ctrl; TYPE_2__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  anx9805_i2c_algo ; 
 int /*<<< orphan*/  anx9805_i2c_func ; 
 int /*<<< orphan*/  i2c_bit_algo ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int) ; 
 int nouveau_i2c_port_create (struct nouveau_object*,struct nouveau_object*,struct nouveau_oclass*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct anx9805_i2c_port**) ; 
 struct nouveau_object* nv_object (struct anx9805_i2c_port*) ; 

__attribute__((used)) static int
anx9805_ddc_port_ctor(struct nouveau_object *parent,
		      struct nouveau_object *engine,
		      struct nouveau_oclass *oclass, void *data, u32 index,
		      struct nouveau_object **pobject)
{
	struct nouveau_i2c_port *mast = (void *)parent;
	struct anx9805_i2c_port *port;
	int ret;

	ret = nouveau_i2c_port_create(parent, engine, oclass, index,
				     &anx9805_i2c_algo, &port);
	*pobject = nv_object(port);
	if (ret)
		return ret;

	switch ((oclass->handle & 0xff00) >> 8) {
	case 0x0d:
		port->addr = 0x3d;
		port->ctrl = 0x39;
		break;
	case 0x0e:
		port->addr = 0x3f;
		port->ctrl = 0x3b;
		break;
	default:
		BUG_ON(1);
	}

	if (mast->adapter.algo == &i2c_bit_algo) {
		struct i2c_algo_bit_data *algo = mast->adapter.algo_data;
		algo->udelay = max(algo->udelay, 40);
	}

	port->base.func = &anx9805_i2c_func;
	return 0;
}