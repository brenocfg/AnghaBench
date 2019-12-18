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
struct nouveau_i2c_port {TYPE_1__* func; } ;
struct i2c_algo_bit_data {struct nouveau_i2c_port* data; } ;
struct i2c_adapter {struct i2c_algo_bit_data* algo_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* acquire ) (struct nouveau_i2c_port*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct nouveau_i2c_port*) ; 

__attribute__((used)) static int
nouveau_i2c_pre_xfer(struct i2c_adapter *adap)
{
	struct i2c_algo_bit_data *bit = adap->algo_data;
	struct nouveau_i2c_port *port = bit->data;
	if (port->func->acquire)
		port->func->acquire(port);
	return 0;
}