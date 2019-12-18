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
struct TYPE_2__ {int /*<<< orphan*/  line; } ;
struct mpsc_port_info {int ready; TYPE_1__ port; } ;

/* Variables and functions */
 int mpsc_alloc_ring_mem (struct mpsc_port_info*) ; 
 int /*<<< orphan*/  mpsc_init_hw (struct mpsc_port_info*) ; 
 int /*<<< orphan*/  mpsc_init_rings (struct mpsc_port_info*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mpsc_make_ready(struct mpsc_port_info *pi)
{
	int rc;

	pr_debug("mpsc_make_ready[%d]: Making cltr ready\n", pi->port.line);

	if (!pi->ready) {
		mpsc_init_hw(pi);
		if ((rc = mpsc_alloc_ring_mem(pi)))
			return rc;
		mpsc_init_rings(pi);
		pi->ready = 1;
	}

	return 0;
}