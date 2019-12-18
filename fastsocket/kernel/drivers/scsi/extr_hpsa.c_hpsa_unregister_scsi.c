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
struct ctlr_info {int /*<<< orphan*/ * scsi_host; } ;

/* Variables and functions */
 int /*<<< orphan*/  scsi_host_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_remove_host (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hpsa_unregister_scsi(struct ctlr_info *h)
{
	/* we are being forcibly unloaded, and may not refuse. */
	scsi_remove_host(h->scsi_host);
	scsi_host_put(h->scsi_host);
	h->scsi_host = NULL;
}