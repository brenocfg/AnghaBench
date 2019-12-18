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
struct hpsa_scsi_dev_t {int /*<<< orphan*/  model; } ;
struct ctlr_info {int dummy; } ;

/* Variables and functions */
 scalar_t__* ext_target_model ; 
 int /*<<< orphan*/  strlen (scalar_t__) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int is_ext_target(struct ctlr_info *h, struct hpsa_scsi_dev_t *device)
{
	int i;

	for (i = 0; ext_target_model[i]; i++) 
		if (strncmp(device->model, ext_target_model[i],
			strlen(ext_target_model[i])) == 0)
			return 1;
	return 0;
}