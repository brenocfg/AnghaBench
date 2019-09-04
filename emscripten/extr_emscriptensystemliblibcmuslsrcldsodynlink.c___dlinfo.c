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
struct link_map {int dummy; } ;

/* Variables and functions */
 int RTLD_DI_LINKMAP ; 
 int /*<<< orphan*/  errbuf ; 
 int errflag ; 
 scalar_t__ invalid_dso_handle (void*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 

int __dlinfo(void *dso, int req, void *res)
{
	if (invalid_dso_handle(dso)) return -1;
	if (req != RTLD_DI_LINKMAP) {
		snprintf(errbuf, sizeof errbuf, "Unsupported request %d", req);
		errflag = 1;
		return -1;
	}
	*(struct link_map **)res = dso;
	return 0;
}