#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  size; int /*<<< orphan*/  address; } ;

/* Variables and functions */
 int /*<<< orphan*/  FDT_CHECK_HEADER (void const*) ; 
 TYPE_1__* _fdt_mem_rsv (void const*,int) ; 
 int /*<<< orphan*/  fdt64_to_cpu (int /*<<< orphan*/ ) ; 

int fdt_get_mem_rsv(const void *fdt, int n, uint64_t *address, uint64_t *size)
{
	FDT_CHECK_HEADER(fdt);
	*address = fdt64_to_cpu(_fdt_mem_rsv(fdt, n)->address);
	*size = fdt64_to_cpu(_fdt_mem_rsv(fdt, n)->size);
	return 0;
}