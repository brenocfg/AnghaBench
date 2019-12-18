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
 int _fdt_splice (void*,void*,int,int) ; 
 scalar_t__ fdt_off_dt_strings (void*) ; 
 int /*<<< orphan*/  fdt_set_off_dt_strings (void*,scalar_t__) ; 
 int /*<<< orphan*/  fdt_set_size_dt_struct (void*,scalar_t__) ; 
 scalar_t__ fdt_size_dt_struct (void*) ; 

__attribute__((used)) static int _fdt_splice_struct(void *fdt, void *p,
			      int oldlen, int newlen)
{
	int delta = newlen - oldlen;
	int err;

	if ((err = _fdt_splice(fdt, p, oldlen, newlen)) != 0)
		return err;

	fdt_set_size_dt_struct(fdt, fdt_size_dt_struct(fdt) + delta);
	fdt_set_off_dt_strings(fdt, fdt_off_dt_strings(fdt) + delta);
	return 0;
}