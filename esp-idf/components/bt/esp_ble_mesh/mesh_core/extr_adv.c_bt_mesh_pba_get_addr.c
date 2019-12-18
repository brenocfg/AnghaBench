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
typedef  int /*<<< orphan*/  bt_mesh_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  const* dev_addr ; 

const bt_mesh_addr_t *bt_mesh_pba_get_addr(void)
{
    return dev_addr;
}