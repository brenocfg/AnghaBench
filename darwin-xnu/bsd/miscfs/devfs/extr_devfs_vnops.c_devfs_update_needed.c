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
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 long DEVFS_LAZY_UPDATE_SECONDS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static boolean_t
devfs_update_needed(long now_s, long last_s)
{
	if (now_s > last_s) {
		if (now_s - last_s >= DEVFS_LAZY_UPDATE_SECONDS) {
			return TRUE;
		}
	}

	return FALSE;
}