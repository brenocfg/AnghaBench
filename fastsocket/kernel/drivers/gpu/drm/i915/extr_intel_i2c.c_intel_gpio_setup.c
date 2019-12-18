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
typedef  int u32 ;
struct TYPE_3__ {struct i2c_algo_bit_data* algo_data; } ;
struct i2c_algo_bit_data {struct intel_gmbus* data; int /*<<< orphan*/  timeout; int /*<<< orphan*/  udelay; int /*<<< orphan*/  post_xfer; int /*<<< orphan*/  pre_xfer; int /*<<< orphan*/  getscl; int /*<<< orphan*/  getsda; int /*<<< orphan*/  setscl; int /*<<< orphan*/  setsda; } ;
struct intel_gmbus {TYPE_1__ adapter; scalar_t__ gpio_reg; struct i2c_algo_bit_data bit_algo; struct drm_i915_private* dev_priv; } ;
struct drm_i915_private {scalar_t__ gpio_mmio_base; } ;
struct TYPE_4__ {scalar_t__ reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_RISEFALL_TIME ; 
 int /*<<< orphan*/  get_clock ; 
 int /*<<< orphan*/  get_data ; 
 TYPE_2__* gmbus_ports ; 
 int /*<<< orphan*/  intel_gpio_post_xfer ; 
 int /*<<< orphan*/  intel_gpio_pre_xfer ; 
 int /*<<< orphan*/  set_clock ; 
 int /*<<< orphan*/  set_data ; 
 int /*<<< orphan*/  usecs_to_jiffies (int) ; 

__attribute__((used)) static void
intel_gpio_setup(struct intel_gmbus *bus, u32 pin)
{
	struct drm_i915_private *dev_priv = bus->dev_priv;
	struct i2c_algo_bit_data *algo;

	algo = &bus->bit_algo;

	/* -1 to map pin pair to gmbus index */
	bus->gpio_reg = dev_priv->gpio_mmio_base + gmbus_ports[pin - 1].reg;

	bus->adapter.algo_data = algo;
	algo->setsda = set_data;
	algo->setscl = set_clock;
	algo->getsda = get_data;
	algo->getscl = get_clock;
	algo->pre_xfer = intel_gpio_pre_xfer;
	algo->post_xfer = intel_gpio_post_xfer;
	algo->udelay = I2C_RISEFALL_TIME;
	algo->timeout = usecs_to_jiffies(2200);
	algo->data = bus;
}