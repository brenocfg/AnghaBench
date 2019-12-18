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
 int check_err (int) ; 
 int /*<<< orphan*/  devp_offset (void const*) ; 
 int /*<<< orphan*/  fdt ; 
 void* fdt_getprop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int*) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int,int const) ; 

__attribute__((used)) static int fdt_wrapper_getprop(const void *devp, const char *name,
			       void *buf, const int buflen)
{
	const void *p;
	int len;

	p = fdt_getprop(fdt, devp_offset(devp), name, &len);
	if (!p)
		return check_err(len);
	memcpy(buf, p, min(len, buflen));
	return len;
}