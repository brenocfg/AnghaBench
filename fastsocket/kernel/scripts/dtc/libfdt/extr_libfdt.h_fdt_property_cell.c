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
typedef  int /*<<< orphan*/  val ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_fdt32 (int /*<<< orphan*/ ) ; 
 int fdt_property (void*,char const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int fdt_property_cell(void *fdt, const char *name, uint32_t val)
{
	val = cpu_to_fdt32(val);
	return fdt_property(fdt, name, &val, sizeof(val));
}