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
typedef  int /*<<< orphan*/  const bt_mesh_atomic_val_t ;
typedef  int /*<<< orphan*/  bt_mesh_atomic_t ;

/* Variables and functions */

bt_mesh_atomic_val_t bt_mesh_atomic_get(const bt_mesh_atomic_t *target)
{
    return *target;
}