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
struct mpsc_port_info {scalar_t__ txr_tail; scalar_t__ txr_head; int /*<<< orphan*/ * txb_p; int /*<<< orphan*/ * txb; scalar_t__ txr_p; scalar_t__ txr; scalar_t__ rxr_posn; int /*<<< orphan*/ * rxb_p; int /*<<< orphan*/ * rxb; scalar_t__ rxr_p; scalar_t__ rxr; int /*<<< orphan*/ * dma_region; TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mpsc_uninit_rings(struct mpsc_port_info *pi)
{
	pr_debug("mpsc_uninit_rings[%d]: Uninitializing rings\n",pi->port.line);

	BUG_ON(pi->dma_region == NULL);

	pi->rxr = 0;
	pi->rxr_p = 0;
	pi->rxb = NULL;
	pi->rxb_p = NULL;
	pi->rxr_posn = 0;

	pi->txr = 0;
	pi->txr_p = 0;
	pi->txb = NULL;
	pi->txb_p = NULL;
	pi->txr_head = 0;
	pi->txr_tail = 0;
}