#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTM_STATUS ;
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_4__ {char* bd_name; } ;
struct TYPE_6__ {TYPE_1__ cfg; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* get_is_ready ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BCM_STRNCPY_S (char*,int,char*,size_t) ; 
 scalar_t__ BD_NAME_LEN ; 
 int /*<<< orphan*/  BTM_CMD_STARTED ; 
 int /*<<< orphan*/  BTM_DEV_RESET ; 
 int /*<<< orphan*/  BTM_ILLEGAL_VALUE ; 
 size_t BTM_MAX_LOC_BD_NAME_LEN ; 
 int /*<<< orphan*/  BTM_NO_RESOURCES ; 
 TYPE_3__ btm_cb ; 
 scalar_t__ btsnd_hcic_change_name (int /*<<< orphan*/ *) ; 
 TYPE_2__* controller_get_interface () ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  stub1 () ; 

tBTM_STATUS BTM_SetLocalDeviceName (char *p_name)
{
    UINT8    *p;

    if (!p_name || !p_name[0] || (strlen ((char *)p_name) > BD_NAME_LEN)) {
        return (BTM_ILLEGAL_VALUE);
    }

    if (!controller_get_interface()->get_is_ready()) {
        return (BTM_DEV_RESET);
    }

#if BTM_MAX_LOC_BD_NAME_LEN > 0
    /* Save the device name if local storage is enabled */
    p = (UINT8 *)btm_cb.cfg.bd_name;
    if (p != (UINT8 *)p_name) {
        BCM_STRNCPY_S(btm_cb.cfg.bd_name, sizeof(btm_cb.cfg.bd_name), p_name, BTM_MAX_LOC_BD_NAME_LEN);
        btm_cb.cfg.bd_name[BTM_MAX_LOC_BD_NAME_LEN] = '\0';
    }
#else
    p = (UINT8 *)p_name;
#endif

    if (btsnd_hcic_change_name(p)) {
        return (BTM_CMD_STARTED);
    } else {
        return (BTM_NO_RESOURCES);
    }
}