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
 int MAX_PATH_LEN ; 
 void* finddevice (char*) ; 
 scalar_t__ getprop (void*,char const*,char*,int) ; 

__attribute__((used)) static inline void *find_node_by_alias(const char *alias)
{
	void *devp = finddevice("/aliases");

	if (devp) {
		char path[MAX_PATH_LEN];
		if (getprop(devp, alias, path, MAX_PATH_LEN) > 0)
			return finddevice(path);
	}

	return NULL;
}