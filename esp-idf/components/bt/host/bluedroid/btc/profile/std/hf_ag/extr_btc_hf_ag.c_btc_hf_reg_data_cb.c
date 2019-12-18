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
typedef  int /*<<< orphan*/  esp_hf_outgoing_data_cb_t ;
typedef  int /*<<< orphan*/  esp_hf_incoming_data_cb_t ;
struct TYPE_2__ {int /*<<< orphan*/  btc_hf_outgoing_data_cb; int /*<<< orphan*/  btc_hf_incoming_data_cb; } ;

/* Variables and functions */
 TYPE_1__* hf_local_param ; 

void btc_hf_reg_data_cb(esp_hf_incoming_data_cb_t recv, esp_hf_outgoing_data_cb_t send)
{
    hf_local_param[0].btc_hf_incoming_data_cb = recv;
    hf_local_param[0].btc_hf_outgoing_data_cb = send;
}