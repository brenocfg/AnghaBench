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
typedef  int /*<<< orphan*/  chassis_timestamps_t ;

/* Variables and functions */
 int /*<<< orphan*/ * chassis_timestamps_global ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 

void chassis_timestamps_global_free(chassis_timestamps_t *gl) {
	if (NULL == gl) {
		g_free(chassis_timestamps_global);
	} else {
		g_free(gl);
	}
}