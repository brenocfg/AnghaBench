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
typedef  size_t tBTA_HF_CLIENT_EVT ;

/* Variables and functions */
 int* bta_hf_client_cb_data_size ; 

int BTA_HfClientGetCbDataSize(tBTA_HF_CLIENT_EVT event)
{
    return bta_hf_client_cb_data_size[event];
}