#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* filename; } ;
typedef  TYPE_1__ DIR_ENTRY ;

/* Variables and functions */

__attribute__((used)) static inline bool _FAT_directory_isDot (DIR_ENTRY* entry) {
	return ((entry->filename[0] == '.') && ((entry->filename[1] == '\0') ||
		((entry->filename[1] == '.') && entry->filename[2] == '\0')));
}