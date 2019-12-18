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

/* Variables and functions */
 int /*<<< orphan*/  osi_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sensor_client_mutex ; 

__attribute__((used)) static void bt_mesh_sensor_client_unlock(void)
{
    osi_mutex_unlock(&sensor_client_mutex);
}