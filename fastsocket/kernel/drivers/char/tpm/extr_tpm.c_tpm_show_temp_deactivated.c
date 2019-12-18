#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_4__ {int deactivated; } ;
struct TYPE_5__ {TYPE_1__ stclear_flags; } ;
typedef  TYPE_2__ cap_t ;

/* Variables and functions */
 int /*<<< orphan*/  TPM_CAP_FLAG_VOL ; 
 scalar_t__ sprintf (char*,char*,int) ; 
 scalar_t__ tpm_getcap (struct device*,int /*<<< orphan*/ ,TYPE_2__*,char*) ; 

ssize_t tpm_show_temp_deactivated(struct device * dev,
				struct device_attribute * attr, char *buf)
{
	cap_t cap;
	ssize_t rc;

	rc = tpm_getcap(dev, TPM_CAP_FLAG_VOL, &cap,
			 "attempting to determine the temporary state");
	if (rc)
		return 0;

	rc = sprintf(buf, "%d\n", cap.stclear_flags.deactivated);
	return rc;
}