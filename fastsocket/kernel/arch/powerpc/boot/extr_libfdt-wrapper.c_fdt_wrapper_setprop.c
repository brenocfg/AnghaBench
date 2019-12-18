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
 int FDT_ERR_NOSPACE ; 
 int check_err (int) ; 
 int /*<<< orphan*/  devp_offset (void const*) ; 
 int /*<<< orphan*/  expand_buf (int const) ; 
 int /*<<< orphan*/  fdt ; 
 int fdt_setprop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,void const*,int const) ; 

__attribute__((used)) static int fdt_wrapper_setprop(const void *devp, const char *name,
			       const void *buf, const int len)
{
	int rc;

	rc = fdt_setprop(fdt, devp_offset(devp), name, buf, len);
	if (rc == -FDT_ERR_NOSPACE) {
		expand_buf(len + 16);
		rc = fdt_setprop(fdt, devp_offset(devp), name, buf, len);
	}

	return check_err(rc);
}