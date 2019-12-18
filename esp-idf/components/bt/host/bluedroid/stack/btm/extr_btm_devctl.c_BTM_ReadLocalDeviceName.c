#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTM_STATUS ;
struct TYPE_3__ {char* bd_name; } ;
struct TYPE_4__ {TYPE_1__ cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_NO_RESOURCES ; 
 int /*<<< orphan*/  BTM_SUCCESS ; 
 TYPE_2__ btm_cb ; 

tBTM_STATUS BTM_ReadLocalDeviceName (char **p_name)
{
#if BTM_MAX_LOC_BD_NAME_LEN > 0
    *p_name = btm_cb.cfg.bd_name;
    return (BTM_SUCCESS);
#else
    *p_name = NULL;
    return (BTM_NO_RESOURCES);
#endif
}