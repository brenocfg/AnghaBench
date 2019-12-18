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
struct TYPE_4__ {int* indicator_lookup; int /*<<< orphan*/  current_cmd; } ;
struct TYPE_5__ {TYPE_1__ at_cb; } ;
struct TYPE_6__ {TYPE_2__ scb; } ;

/* Variables and functions */
 int BTA_HF_CLIENT_AT_INDICATOR_COUNT ; 
 int /*<<< orphan*/  BTA_HF_CLIENT_AT_NONE ; 
 int /*<<< orphan*/  bta_hf_client_at_clear_buf () ; 
 TYPE_3__ bta_hf_client_cb ; 
 int /*<<< orphan*/  bta_hf_client_clear_queued_at () ; 
 int /*<<< orphan*/  bta_hf_client_free_at_hold_timer () ; 
 int /*<<< orphan*/  bta_hf_client_free_at_resp_timer () ; 

void bta_hf_client_at_reset(void)
{
    int i;

    bta_hf_client_free_at_resp_timer();
    bta_hf_client_free_at_hold_timer();

    bta_hf_client_clear_queued_at();

    bta_hf_client_at_clear_buf();

    for (i = 0; i < BTA_HF_CLIENT_AT_INDICATOR_COUNT; i++) {
        bta_hf_client_cb.scb.at_cb.indicator_lookup[i] = -1;
    }

    bta_hf_client_cb.scb.at_cb.current_cmd = BTA_HF_CLIENT_AT_NONE;
}