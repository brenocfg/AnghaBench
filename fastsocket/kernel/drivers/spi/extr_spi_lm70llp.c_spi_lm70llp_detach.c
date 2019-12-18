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
struct TYPE_2__ {int /*<<< orphan*/  master; } ;
struct spi_lm70llp {TYPE_1__ bitbang; int /*<<< orphan*/  pd; struct parport* port; } ;
struct parport {int dummy; } ;

/* Variables and functions */
 struct spi_lm70llp* lm70llp ; 
 int /*<<< orphan*/  parport_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parport_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parport_write_data (struct parport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_bitbang_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  spi_master_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void spi_lm70llp_detach(struct parport *p)
{
	struct spi_lm70llp		*pp;

	if (!lm70llp || lm70llp->port != p)
		return;

	pp = lm70llp;
	spi_bitbang_stop(&pp->bitbang);

	/* power down */
	parport_write_data(pp->port, 0);

	parport_release(pp->pd);
	parport_unregister_device(pp->pd);

	(void) spi_master_put(pp->bitbang.master);

	lm70llp = NULL;
}