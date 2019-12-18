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
struct pnp_dev {int /*<<< orphan*/ * card; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  isapnp_id; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ISAPNP_FUNCTION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISAPNP_VENDOR (char,char,char) ; 
 int n_ni_boards ; 
 TYPE_1__* ni_boards ; 
 scalar_t__ pnp_activate_dev (struct pnp_dev*) ; 
 scalar_t__ pnp_device_attach (struct pnp_dev*) ; 
 int /*<<< orphan*/  pnp_device_detach (struct pnp_dev*) ; 
 struct pnp_dev* pnp_find_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pnp_irq_valid (struct pnp_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnp_port_valid (struct pnp_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static int ni_isapnp_find_board(struct pnp_dev **dev)
{
	struct pnp_dev *isapnp_dev = NULL;
	int i;

	for (i = 0; i < n_ni_boards; i++) {
		isapnp_dev = pnp_find_dev(NULL,
					  ISAPNP_VENDOR('N', 'I', 'C'),
					  ISAPNP_FUNCTION(ni_boards[i].
							  isapnp_id), NULL);

		if (isapnp_dev == NULL || isapnp_dev->card == NULL)
			continue;

		if (pnp_device_attach(isapnp_dev) < 0) {
			printk
			    ("ni_atmio: %s found but already active, skipping.\n",
			     ni_boards[i].name);
			continue;
		}
		if (pnp_activate_dev(isapnp_dev) < 0) {
			pnp_device_detach(isapnp_dev);
			return -EAGAIN;
		}
		if (!pnp_port_valid(isapnp_dev, 0)
		    || !pnp_irq_valid(isapnp_dev, 0)) {
			pnp_device_detach(isapnp_dev);
			printk("ni_atmio: pnp invalid port or irq, aborting\n");
			return -ENOMEM;
		}
		break;
	}
	if (i == n_ni_boards)
		return -ENODEV;
	*dev = isapnp_dev;
	return 0;
}