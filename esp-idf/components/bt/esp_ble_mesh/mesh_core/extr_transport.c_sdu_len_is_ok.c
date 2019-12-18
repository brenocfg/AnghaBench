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
typedef  int u8_t ;

/* Variables and functions */
 int CONFIG_BLE_MESH_RX_SDU_MAX ; 
 int seg_len (int) ; 

__attribute__((used)) static inline bool sdu_len_is_ok(bool ctl, u8_t seg_n)
{
    return ((seg_n * seg_len(ctl) + 1) <= CONFIG_BLE_MESH_RX_SDU_MAX);
}