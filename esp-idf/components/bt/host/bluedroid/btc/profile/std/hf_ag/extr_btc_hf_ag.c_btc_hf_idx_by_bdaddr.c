#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ address; } ;
typedef  TYPE_3__ bt_bdaddr_t ;
struct TYPE_6__ {int /*<<< orphan*/  address; } ;
struct TYPE_7__ {TYPE_1__ connected_bda; } ;
struct TYPE_9__ {TYPE_2__ btc_hf_cb; } ;

/* Variables and functions */
 int BTC_HF_INVALID_IDX ; 
 scalar_t__ bdcmp (scalar_t__,int /*<<< orphan*/ ) ; 
 int btc_max_hf_clients ; 
 TYPE_4__* hf_local_param ; 

__attribute__((used)) static int btc_hf_idx_by_bdaddr(bt_bdaddr_t *bd_addr)
{
    for (int i = 0; i < btc_max_hf_clients; ++i) {
        if ((bdcmp(bd_addr->address, hf_local_param[i].btc_hf_cb.connected_bda.address) == 0)
            || bd_addr->address) {
            return i;
        }
    }
    return BTC_HF_INVALID_IDX;
}