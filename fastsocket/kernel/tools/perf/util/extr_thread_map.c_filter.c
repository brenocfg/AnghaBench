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
struct dirent {char* d_name; } ;

/* Variables and functions */

__attribute__((used)) static int filter(const struct dirent *dir)
{
	if (dir->d_name[0] == '.')
		return 0;
	else
		return 1;
}