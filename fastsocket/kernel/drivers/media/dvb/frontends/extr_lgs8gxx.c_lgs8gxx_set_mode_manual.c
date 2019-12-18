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
 scalar_t__ LGS8GXX_PROD_LGS8913 ; 
 scalar_t__ LGS8GXX_PROD_LGS8G75 ; 
 int lgs8gxx_read_reg (struct lgs8gxx_state*,int,int*) ; 
 int /*<<< orphan*/  lgs8gxx_soft_reset (struct lgs8gxx_state*) ; 
 int /*<<< orphan*/  lgs8gxx_write_reg (struct lgs8gxx_state*,int,int) ; 

__attribute__((used)) static int lgs8gxx_set_mode_manual(struct lgs8gxx_state *priv)
{
	int ret = 0;
	u8 t;

	if (priv->config->prod == LGS8GXX_PROD_LGS8G75) {
		u8 t2;
		lgs8gxx_read_reg(priv, 0x0C, &t);
		t &= (~0x80);
		lgs8gxx_write_reg(priv, 0x0C, t);

		lgs8gxx_read_reg(priv, 0x0C, &t);
		lgs8gxx_read_reg(priv, 0x19, &t2);

		if (((t&0x03) == 0x01) && (t2&0x01)) {
			lgs8gxx_write_reg(priv, 0x6E, 0x05);
			lgs8gxx_write_reg(priv, 0x39, 0x02);
			lgs8gxx_write_reg(priv, 0x39, 0x03);
			lgs8gxx_write_reg(priv, 0x3D, 0x05);
			lgs8gxx_write_reg(priv, 0x3E, 0x28);
			lgs8gxx_write_reg(priv, 0x53, 0x80);
		} else {
			lgs8gxx_write_reg(priv, 0x6E, 0x3F);
			lgs8gxx_write_reg(priv, 0x39, 0x00);
			lgs8gxx_write_reg(priv, 0x3D, 0x04);
		}

		lgs8gxx_soft_reset(priv);
		return 0;
	}

	/* turn off auto-detect; manual settings */
	lgs8gxx_write_reg(priv, 0x7E, 0);
	if (priv->config->prod == LGS8GXX_PROD_LGS8913)
		lgs8gxx_write_reg(priv, 0xC1, 0);

	ret = lgs8gxx_read_reg(priv, 0xC5, &t);
	t = (t & 0xE0) | 0x06;
	lgs8gxx_write_reg(priv, 0xC5, t);

	lgs8gxx_soft_reset(priv);

	return 0;
}