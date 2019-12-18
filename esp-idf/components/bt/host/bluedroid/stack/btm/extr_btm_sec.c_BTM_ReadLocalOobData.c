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
typedef  int /*<<< orphan*/  tBTM_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_NO_RESOURCES ; 
 int /*<<< orphan*/  BTM_SUCCESS ; 
 scalar_t__ FALSE ; 
 scalar_t__ btsnd_hcic_read_local_oob_data () ; 

tBTM_STATUS BTM_ReadLocalOobData(void)
{
    tBTM_STATUS status = BTM_SUCCESS;

    if (btsnd_hcic_read_local_oob_data() == FALSE) {
        status = BTM_NO_RESOURCES;
    }

    return status;
}