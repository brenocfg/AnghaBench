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
typedef  int UBYTE ;

/* Variables and functions */
 scalar_t__ ENOTEMPTY ; 
 scalar_t__ errno ; 
 scalar_t__ rmdir (char const*) ; 

__attribute__((used)) static UBYTE Devices_RemoveDirectory(const char *filename)
{
	if (rmdir(filename) == 0)
		return 1;
	return (UBYTE) ((errno == ENOTEMPTY) ? 167 : 150);
}