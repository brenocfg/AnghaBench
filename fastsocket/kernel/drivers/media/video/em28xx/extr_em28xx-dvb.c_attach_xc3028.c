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
struct xc2028_config {int /*<<< orphan*/  i2c_addr; int /*<<< orphan*/ * i2c_adap; } ;
struct em28xx {int /*<<< orphan*/  name; TYPE_1__* dvb; int /*<<< orphan*/  i2c_adap; } ;
struct dvb_frontend {int dummy; } ;
typedef  int /*<<< orphan*/  cfg ;
struct TYPE_2__ {int /*<<< orphan*/ * frontend; } ;

/* Variables and functions */
 int EINVAL ; 
 struct dvb_frontend* dvb_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct xc2028_config*) ; 
 int /*<<< orphan*/  dvb_frontend_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  em28xx_errdev (char*) ; 
 int /*<<< orphan*/  em28xx_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct xc2028_config*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xc2028_attach ; 

__attribute__((used)) static int attach_xc3028(u8 addr, struct em28xx *dev)
{
	struct dvb_frontend *fe;
	struct xc2028_config cfg;

	memset(&cfg, 0, sizeof(cfg));
	cfg.i2c_adap  = &dev->i2c_adap;
	cfg.i2c_addr  = addr;

	if (!dev->dvb->frontend) {
		em28xx_errdev("/2: dvb frontend not attached. "
				"Can't attach xc3028\n");
		return -EINVAL;
	}

	fe = dvb_attach(xc2028_attach, dev->dvb->frontend, &cfg);
	if (!fe) {
		em28xx_errdev("/2: xc3028 attach failed\n");
		dvb_frontend_detach(dev->dvb->frontend);
		dev->dvb->frontend = NULL;
		return -EINVAL;
	}

	em28xx_info("%s/2: xc3028 attached\n", dev->name);

	return 0;
}