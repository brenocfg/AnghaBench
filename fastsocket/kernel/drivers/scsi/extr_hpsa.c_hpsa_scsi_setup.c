#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ctlr_info {int /*<<< orphan*/  devlock; int /*<<< orphan*/ * scsi_host; scalar_t__ ndevices; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hpsa_scsi_setup(struct ctlr_info *h)
{
	h->ndevices = 0;
	h->scsi_host = NULL;
	spin_lock_init(&h->devlock);
}