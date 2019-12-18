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
struct em28xx {int dummy; } ;
struct dvb_frontend {TYPE_1__* dvb; } ;
struct TYPE_2__ {struct em28xx* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  EM28XX_DIGITAL_MODE ; 
 int /*<<< orphan*/  EM28XX_SUSPEND ; 
 int em28xx_set_mode (struct em28xx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int em28xx_dvb_bus_ctrl(struct dvb_frontend *fe, int acquire)
{
	struct em28xx *dev = fe->dvb->priv;

	if (acquire)
		return em28xx_set_mode(dev, EM28XX_DIGITAL_MODE);
	else
		return em28xx_set_mode(dev, EM28XX_SUSPEND);
}