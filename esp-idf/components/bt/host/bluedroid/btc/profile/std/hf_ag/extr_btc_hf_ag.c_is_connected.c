#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  address; } ;
typedef  TYPE_3__ bt_bdaddr_t ;
struct TYPE_7__ {int /*<<< orphan*/  address; } ;
struct TYPE_8__ {scalar_t__ connection_state; TYPE_1__ connected_bda; } ;
struct TYPE_10__ {TYPE_2__ btc_hf_cb; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 scalar_t__ ESP_HF_CONNECTION_STATE_CONNECTED ; 
 scalar_t__ ESP_HF_CONNECTION_STATE_SLC_CONNECTED ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ bdcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int btc_hf_idx_by_bdaddr (TYPE_3__*) ; 
 TYPE_5__* hf_local_param ; 

__attribute__((used)) static BOOLEAN is_connected(bt_bdaddr_t *bd_addr)
{
    int idx = btc_hf_idx_by_bdaddr(bd_addr);
    if (((hf_local_param[idx].btc_hf_cb.connection_state == ESP_HF_CONNECTION_STATE_CONNECTED) ||
            (hf_local_param[idx].btc_hf_cb.connection_state == ESP_HF_CONNECTION_STATE_SLC_CONNECTED)) &&
            ((bd_addr == NULL) || (bdcmp(bd_addr->address,hf_local_param[idx].btc_hf_cb.connected_bda.address) == 0))) {
        return TRUE;
    }
    return FALSE;
}