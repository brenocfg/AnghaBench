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
 int /*<<< orphan*/  health_client_mutex ; 
 int /*<<< orphan*/  osi_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bt_mesh_health_client_unlock(void)
{
    osi_mutex_unlock(&health_client_mutex);
}