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
struct scsi_host_template {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * __fdomain_16x0_detect (struct scsi_host_template*) ; 
 scalar_t__ fdomain ; 
 int /*<<< orphan*/  fdomain_setup (scalar_t__) ; 

__attribute__((used)) static int fdomain_16x0_detect(struct scsi_host_template *tpnt)
{
	if (fdomain)
		fdomain_setup(fdomain);
	return (__fdomain_16x0_detect(tpnt) != NULL);
}