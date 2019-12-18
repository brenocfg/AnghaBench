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
struct lgs8gxx_state {TYPE_1__* config; } ;
struct TYPE_2__ {scalar_t__ prod; } ;

/* Variables and functions */
 scalar_t__ LGS8GXX_PROD_LGS8G75 ; 
 int wait_reg_mask (struct lgs8gxx_state*,int,int,int,int,int) ; 

__attribute__((used)) static int lgs8gxx_wait_ca_lock(struct lgs8gxx_state *priv, u8 *locked)
{
	int ret = 0;
	u8 reg, mask, val;

	if (priv->config->prod == LGS8GXX_PROD_LGS8G75) {
		reg = 0x13;
		mask = 0x80;
		val = 0x80;
	} else {
		reg = 0x4B;
		mask = 0xC0;
		val = 0xC0;
	}

	ret = wait_reg_mask(priv, reg, mask, val, 50, 40);
	*locked = (ret == 0) ? 1 : 0;

	return 0;
}