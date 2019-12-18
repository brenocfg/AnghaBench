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
typedef  int UINT8 ;
struct TYPE_4__ {int* irk_list_mask; } ;
struct TYPE_6__ {TYPE_1__ ble_ctr_cb; } ;
struct TYPE_5__ {int (* get_ble_resolving_list_max_size ) () ;} ;

/* Variables and functions */
 TYPE_3__ btm_cb ; 
 TYPE_2__* controller_get_interface () ; 
 int stub1 () ; 

void btm_ble_clear_irk_index(UINT8 index)
{
    UINT8 byte;
    UINT8 bit;

    if (index < controller_get_interface()->get_ble_resolving_list_max_size()) {
        byte = index / 8;
        bit = index % 8;
        btm_cb.ble_ctr_cb.irk_list_mask[byte] &= (~(1 << bit));
    }
}