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
struct intel_sdvo {TYPE_2__* i2c; int /*<<< orphan*/  ddc_bus; } ;
struct i2c_msg {int dummy; } ;
struct i2c_adapter {struct intel_sdvo* algo_data; } ;
struct TYPE_4__ {TYPE_1__* algo; } ;
struct TYPE_3__ {int (* master_xfer ) (TYPE_2__*,struct i2c_msg*,int) ;} ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  intel_sdvo_set_control_bus_switch (struct intel_sdvo*,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__*,struct i2c_msg*,int) ; 

__attribute__((used)) static int intel_sdvo_ddc_proxy_xfer(struct i2c_adapter *adapter,
				     struct i2c_msg *msgs,
				     int num)
{
	struct intel_sdvo *sdvo = adapter->algo_data;

	if (!intel_sdvo_set_control_bus_switch(sdvo, sdvo->ddc_bus))
		return -EIO;

	return sdvo->i2c->algo->master_xfer(sdvo->i2c, msgs, num);
}