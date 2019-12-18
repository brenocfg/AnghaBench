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
typedef  enum sas_dev_type { ____Placeholder_sas_dev_type } sas_dev_type ;

/* Variables and functions */
 int SAS_END_DEV ; 
 int SATA_PENDING ; 

__attribute__((used)) static bool dev_type_flutter(enum sas_dev_type new, enum sas_dev_type old)
{
	if (old == new)
		return true;

	/* treat device directed resets as flutter, if we went
	 * SAS_END_DEV to SATA_PENDING the link needs recovery
	 */
	if ((old == SATA_PENDING && new == SAS_END_DEV) ||
	    (old == SAS_END_DEV && new == SATA_PENDING))
		return true;

	return false;
}