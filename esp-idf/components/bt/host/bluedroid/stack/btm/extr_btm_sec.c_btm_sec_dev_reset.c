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
struct TYPE_4__ {int /*<<< orphan*/  loc_io_caps; } ;
struct TYPE_6__ {int /*<<< orphan*/  security_mode; TYPE_1__ devcb; } ;
struct TYPE_5__ {scalar_t__ (* supports_simple_pairing ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_LOCAL_IO_CAPS ; 
 int /*<<< orphan*/  BTM_SEC_MODE_SERVICE ; 
 int /*<<< orphan*/  BTM_SEC_NONE ; 
 int /*<<< orphan*/  BTM_SEC_PROTO_RFCOMM ; 
 int /*<<< orphan*/  BTM_SEC_SERVICE_RFC_MUX ; 
 int /*<<< orphan*/  BTM_SetSecurityLevel (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BT_PSM_RFCOMM ; 
 int /*<<< orphan*/  FALSE ; 
 TYPE_3__ btm_cb ; 
 TYPE_2__* controller_get_interface () ; 
 scalar_t__ stub1 () ; 

void btm_sec_dev_reset (void)
{
    if (controller_get_interface()->supports_simple_pairing()) {
        /* set the default IO capabilities */
        btm_cb.devcb.loc_io_caps = BTM_LOCAL_IO_CAPS;
        /* add mx service to use no security */
        BTM_SetSecurityLevel(FALSE, "RFC_MUX\n", BTM_SEC_SERVICE_RFC_MUX,
                             BTM_SEC_NONE, BT_PSM_RFCOMM, BTM_SEC_PROTO_RFCOMM, 0);
    } else {
        btm_cb.security_mode = BTM_SEC_MODE_SERVICE;
    }

    BTM_TRACE_DEBUG ("btm_sec_dev_reset sec mode: %d\n", btm_cb.security_mode);
}