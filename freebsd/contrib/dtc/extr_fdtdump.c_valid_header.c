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
struct fdt_header {int dummy; } ;
typedef  int off_t ;

/* Variables and functions */
 scalar_t__ FDT_MAGIC ; 
 scalar_t__ MAX_VERSION ; 
 scalar_t__ fdt_last_comp_version (char*) ; 
 scalar_t__ fdt_magic (char*) ; 
 int fdt_off_dt_strings (char*) ; 
 int fdt_off_dt_struct (char*) ; 
 int fdt_totalsize (char*) ; 
 scalar_t__ fdt_version (char*) ; 

__attribute__((used)) static bool valid_header(char *p, off_t len)
{
	if (len < sizeof(struct fdt_header) ||
	    fdt_magic(p) != FDT_MAGIC ||
	    fdt_version(p) > MAX_VERSION ||
	    fdt_last_comp_version(p) >= MAX_VERSION ||
	    fdt_totalsize(p) >= len ||
	    fdt_off_dt_struct(p) >= len ||
	    fdt_off_dt_strings(p) >= len)
		return 0;
	else
		return 1;
}