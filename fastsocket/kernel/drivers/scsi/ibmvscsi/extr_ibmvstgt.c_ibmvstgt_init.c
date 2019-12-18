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
 int ENOMEM ; 
 int /*<<< orphan*/  create_workqueue (char*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int get_system_info () ; 
 int /*<<< orphan*/  ibmvstgt_driver ; 
 int /*<<< orphan*/  ibmvstgt_transport_functions ; 
 int /*<<< orphan*/  ibmvstgt_transport_template ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  srp_attach_transport (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srp_release_transport (int /*<<< orphan*/ ) ; 
 int vio_register_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vtgtd ; 

__attribute__((used)) static int ibmvstgt_init(void)
{
	int err = -ENOMEM;

	printk("IBM eServer i/pSeries Virtual SCSI Target Driver\n");

	ibmvstgt_transport_template =
		srp_attach_transport(&ibmvstgt_transport_functions);
	if (!ibmvstgt_transport_template)
		return err;

	vtgtd = create_workqueue("ibmvtgtd");
	if (!vtgtd)
		goto release_transport;

	err = get_system_info();
	if (err)
		goto destroy_wq;

	err = vio_register_driver(&ibmvstgt_driver);
	if (err)
		goto destroy_wq;

	return 0;
destroy_wq:
	destroy_workqueue(vtgtd);
release_transport:
	srp_release_transport(ibmvstgt_transport_template);
	return err;
}