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
typedef  int /*<<< orphan*/  bt_status_t ;
typedef  int /*<<< orphan*/  bt_bdaddr_t ;
struct TYPE_3__ {int /*<<< orphan*/  handle; } ;
struct TYPE_4__ {TYPE_1__ btc_hf_client_cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_HfClientClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BT_STATUS_FAIL ; 
 int /*<<< orphan*/  BT_STATUS_SUCCESS ; 
 int /*<<< orphan*/  CHECK_HF_CLIENT_INIT () ; 
 TYPE_2__ hf_client_local_param ; 
 scalar_t__ is_connected (int /*<<< orphan*/ *) ; 

bt_status_t btc_hf_client_disconnect( bt_bdaddr_t *bd_addr )
{
    CHECK_HF_CLIENT_INIT();

    if (is_connected(bd_addr))
    {
        BTA_HfClientClose(hf_client_local_param.btc_hf_client_cb.handle);
        return BT_STATUS_SUCCESS;
    }

    return BT_STATUS_FAIL;
}