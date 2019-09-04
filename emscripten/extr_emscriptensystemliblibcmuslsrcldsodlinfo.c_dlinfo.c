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
 scalar_t__ __dl_invalid_handle (void*) ; 
 int /*<<< orphan*/  __dl_seterr (char*,int) ; 

int dlinfo(void *dso, int req, void *res)
{
	if (__dl_invalid_handle(dso)) return -1;
	if (req != RTLD_DI_LINKMAP) {
		__dl_seterr("Unsupported request %d", req);
		return -1;
	}
	*(struct link_map **)res = dso;
	return 0;
}