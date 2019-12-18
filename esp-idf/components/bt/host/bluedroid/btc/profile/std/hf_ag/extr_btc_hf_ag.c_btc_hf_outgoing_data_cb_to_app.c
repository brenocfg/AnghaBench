#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* btc_hf_outgoing_data_cb ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_1__* hf_local_param ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

uint32_t btc_hf_outgoing_data_cb_to_app(uint8_t *data, uint32_t len)
{
    int idx = 0;
    // todo: critical section protection
    if (hf_local_param[idx].btc_hf_outgoing_data_cb) {
        return hf_local_param[idx].btc_hf_outgoing_data_cb(data, len);
    } else {
        return 0;
    }
}