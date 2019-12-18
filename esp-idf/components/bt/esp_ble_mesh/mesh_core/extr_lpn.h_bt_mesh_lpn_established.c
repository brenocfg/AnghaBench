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
struct TYPE_3__ {int established; } ;
struct TYPE_4__ {TYPE_1__ lpn; } ;

/* Variables and functions */
 TYPE_2__ bt_mesh ; 

__attribute__((used)) static inline bool bt_mesh_lpn_established(void)
{
#if defined(CONFIG_BLE_MESH_LOW_POWER)
    return bt_mesh.lpn.established;
#else
    return false;
#endif
}