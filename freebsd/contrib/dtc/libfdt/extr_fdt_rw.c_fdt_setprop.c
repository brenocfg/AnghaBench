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
struct fdt_property {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int FDT_ERR_NOTFOUND ; 
 int /*<<< orphan*/  FDT_RW_CHECK_HEADER (void*) ; 
 int _fdt_add_property (void*,int,char const*,int,struct fdt_property**) ; 
 int _fdt_resize_property (void*,int,char const*,int,struct fdt_property**) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,int) ; 

int fdt_setprop(void *fdt, int nodeoffset, const char *name,
		const void *val, int len)
{
	struct fdt_property *prop;
	int err;

	FDT_RW_CHECK_HEADER(fdt);

	err = _fdt_resize_property(fdt, nodeoffset, name, len, &prop);
	if (err == -FDT_ERR_NOTFOUND)
		err = _fdt_add_property(fdt, nodeoffset, name, len, &prop);
	if (err)
		return err;

	if (len)
		memcpy(prop->data, val, len);
	return 0;
}