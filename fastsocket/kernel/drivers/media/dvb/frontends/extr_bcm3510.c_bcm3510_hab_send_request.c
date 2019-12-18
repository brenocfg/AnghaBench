#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct bcm3510_state {int dummy; } ;
struct TYPE_7__ {int HABR; int LDHABR; } ;
struct TYPE_6__ {scalar_t__ HABADR; } ;
struct TYPE_8__ {TYPE_2__ HABSTAT_a8; scalar_t__ raw; int /*<<< orphan*/  HABDATA_a7; TYPE_1__ HABADR_a6; } ;
typedef  TYPE_3__ bcm3510_register_value ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int HZ ; 
 int bcm3510_readB (struct bcm3510_state*,int,TYPE_3__*) ; 
 int bcm3510_writeB (struct bcm3510_state*,int,TYPE_3__) ; 
 int /*<<< orphan*/  deb_info (char*) ; 
 int jiffies ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ time_before (int,unsigned long) ; 

__attribute__((used)) static int bcm3510_hab_send_request(struct bcm3510_state *st, u8 *buf, int len)
{
	bcm3510_register_value v,hab;
	int ret,i;
	unsigned long t;

/* Check if any previous HAB request still needs to be serviced by the
 * Aquisition Processor before sending new request */
	if ((ret = bcm3510_readB(st,0xa8,&v)) < 0)
		return ret;
	if (v.HABSTAT_a8.HABR) {
		deb_info("HAB is running already - clearing it.\n");
		v.HABSTAT_a8.HABR = 0;
		bcm3510_writeB(st,0xa8,v);
//		return -EBUSY;
	}

/* Send the start HAB Address (automatically incremented after write of
 * HABDATA) and write the HAB Data */
	hab.HABADR_a6.HABADR = 0;
	if ((ret = bcm3510_writeB(st,0xa6,hab)) < 0)
		return ret;

	for (i = 0; i < len; i++) {
		hab.HABDATA_a7 = buf[i];
		if ((ret = bcm3510_writeB(st,0xa7,hab)) < 0)
			return ret;
	}

/* Set the HABR bit to indicate AP request in progress (LBHABR allows HABR to
 * be written) */
	v.raw = 0; v.HABSTAT_a8.HABR = 1; v.HABSTAT_a8.LDHABR = 1;
	if ((ret = bcm3510_writeB(st,0xa8,v)) < 0)
		return ret;

/* Polling method: Wait until the AP finishes processing the HAB request */
	t = jiffies + 1*HZ;
	while (time_before(jiffies, t)) {
		deb_info("waiting for HAB to complete\n");
		msleep(10);
		if ((ret = bcm3510_readB(st,0xa8,&v)) < 0)
			return ret;

		if (!v.HABSTAT_a8.HABR)
			return 0;
	}

	deb_info("send_request execution timed out.\n");
	return -ETIMEDOUT;
}