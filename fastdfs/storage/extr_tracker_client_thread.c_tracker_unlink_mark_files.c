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
 int storage_unlink_mark_file (char const*) ; 
 scalar_t__ trunk_unlink_mark_file (char const*) ; 

__attribute__((used)) static int tracker_unlink_mark_files(const char *storage_id)
{
	int result;

	result = storage_unlink_mark_file(storage_id);
	result += trunk_unlink_mark_file(storage_id);

	return result;
}