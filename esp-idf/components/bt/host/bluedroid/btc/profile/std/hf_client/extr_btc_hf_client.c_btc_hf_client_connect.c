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
typedef  int /*<<< orphan*/  bt_status_t ;
typedef  int /*<<< orphan*/  bt_bdaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_TRACE_EVENT (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_HF_CLIENT_INIT () ; 
 int /*<<< orphan*/  UUID_SERVCLASS_HF_HANDSFREE ; 
 int /*<<< orphan*/  btc_hf_client_version ; 
 int /*<<< orphan*/  btc_queue_connect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  connect_int ; 

bt_status_t btc_hf_client_connect( bt_bdaddr_t *bd_addr )
{
    BTC_TRACE_EVENT("HFP Client version is  %s", btc_hf_client_version);
    CHECK_HF_CLIENT_INIT();
    return btc_queue_connect(UUID_SERVCLASS_HF_HANDSFREE, bd_addr, connect_int);

}