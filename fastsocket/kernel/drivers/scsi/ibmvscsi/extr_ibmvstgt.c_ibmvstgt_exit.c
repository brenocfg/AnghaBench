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

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvstgt_driver ; 
 int /*<<< orphan*/  ibmvstgt_transport_template ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  srp_release_transport (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vio_unregister_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vtgtd ; 

__attribute__((used)) static void ibmvstgt_exit(void)
{
	printk("Unregister IBM virtual SCSI driver\n");

	destroy_workqueue(vtgtd);
	vio_unregister_driver(&ibmvstgt_driver);
	srp_release_transport(ibmvstgt_transport_template);
}