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
typedef  int /*<<< orphan*/  ifnet_family_t ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  NSI_IF_FAM_ID ; 
 int /*<<< orphan*/  net_str_id_find_internal (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

errno_t
ifnet_interface_family_find(const char *module_string,
    ifnet_family_t *family_id)
{
	if (module_string == NULL || family_id == NULL)
		return (EINVAL);

	return (net_str_id_find_internal(module_string, family_id,
	    NSI_IF_FAM_ID, 1));
}