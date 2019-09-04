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
 int /*<<< orphan*/  NAME_MAX ; 
 char* __shm_mapname (char const*,char*) ; 
 int unlink (char const*) ; 

int shm_unlink(const char *name)
{
	char buf[NAME_MAX+10];
	if (!(name = __shm_mapname(name, buf))) return -1;
	return unlink(name);
}