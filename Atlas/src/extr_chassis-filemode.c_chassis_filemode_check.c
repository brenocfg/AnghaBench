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
typedef  int /*<<< orphan*/  gchar ;

/* Variables and functions */
 int /*<<< orphan*/  CHASSIS_FILEMODE_SECURE_MASK ; 
 int chassis_filemode_check_full (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int chassis_filemode_check(const gchar *filename) {
	return chassis_filemode_check_full(filename, CHASSIS_FILEMODE_SECURE_MASK, NULL);
}