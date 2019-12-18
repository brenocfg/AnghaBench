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
struct parport {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  master; } ;
struct butterfly {TYPE_1__ bitbang; int /*<<< orphan*/  pd; struct parport* port; } ;

/* Variables and functions */
 struct butterfly* butterfly ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  parport_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parport_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parport_write_data (struct parport*,int /*<<< orphan*/ ) ; 
 int spi_bitbang_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  spi_master_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void butterfly_detach(struct parport *p)
{
	struct butterfly	*pp;
	int			status;

	/* FIXME this global is ugly ... but, how to quickly get from
	 * the parport to the "struct butterfly" associated with it?
	 * "old school" driver-internal device lists?
	 */
	if (!butterfly || butterfly->port != p)
		return;
	pp = butterfly;
	butterfly = NULL;

	/* stop() unregisters child devices too */
	status = spi_bitbang_stop(&pp->bitbang);

	/* turn off VCC */
	parport_write_data(pp->port, 0);
	msleep(10);

	parport_release(pp->pd);
	parport_unregister_device(pp->pd);

	(void) spi_master_put(pp->bitbang.master);
}