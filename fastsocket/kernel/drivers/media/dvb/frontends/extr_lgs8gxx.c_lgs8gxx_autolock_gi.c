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
 int GI_420 ; 
 int GI_595 ; 
 int GI_945 ; 
 int GI_MASK ; 
 scalar_t__ LGS8GXX_PROD_LGS8G75 ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int lgs8gxx_is_autodetect_finished (struct lgs8gxx_state*,int*) ; 
 int /*<<< orphan*/  lgs8gxx_read_reg (struct lgs8gxx_state*,int,int*) ; 
 int /*<<< orphan*/  lgs8gxx_soft_reset (struct lgs8gxx_state*) ; 
 int lgs8gxx_wait_ca_lock (struct lgs8gxx_state*,int*) ; 
 int /*<<< orphan*/  lgs8gxx_write_reg (struct lgs8gxx_state*,int,int) ; 

__attribute__((used)) static int lgs8gxx_autolock_gi(struct lgs8gxx_state *priv, u8 gi, u8 cpn,
	u8 *locked)
{
	int err = 0;
	u8 ad_fini = 0;
	u8 t1, t2;

	if (gi == GI_945)
		dprintk("try GI 945\n");
	else if (gi == GI_595)
		dprintk("try GI 595\n");
	else if (gi == GI_420)
		dprintk("try GI 420\n");
	if (priv->config->prod == LGS8GXX_PROD_LGS8G75) {
		lgs8gxx_read_reg(priv, 0x0C, &t1);
		lgs8gxx_read_reg(priv, 0x18, &t2);
		t1 &= ~(GI_MASK);
		t1 |= gi;
		t2 &= 0xFE;
		t2 |= cpn ? 0x01 : 0x00;
		lgs8gxx_write_reg(priv, 0x0C, t1);
		lgs8gxx_write_reg(priv, 0x18, t2);
	} else {
		lgs8gxx_write_reg(priv, 0x04, gi);
	}
	lgs8gxx_soft_reset(priv);
	err = lgs8gxx_wait_ca_lock(priv, locked);
	if (err || !(*locked))
		return err;
	err = lgs8gxx_is_autodetect_finished(priv, &ad_fini);
	if (err != 0)
		return err;
	if (ad_fini) {
		dprintk("auto detect finished\n");
	} else
		*locked = 0;

	return 0;
}