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
 scalar_t__ bfad_im_scsi_transport_template ; 
 scalar_t__ bfad_im_scsi_vport_transport_template ; 
 int /*<<< orphan*/  fc_release_transport (scalar_t__) ; 

void
bfad_im_module_exit(void)
{
	if (bfad_im_scsi_transport_template)
		fc_release_transport(bfad_im_scsi_transport_template);

	if (bfad_im_scsi_vport_transport_template)
		fc_release_transport(bfad_im_scsi_vport_transport_template);
}