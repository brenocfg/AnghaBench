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
typedef  void fdt_reserve_entry ;

/* Variables and functions */
 scalar_t__ _fdt_mem_rsv (void*,int) ; 

__attribute__((used)) static inline struct fdt_reserve_entry *_fdt_mem_rsv_w(void *fdt, int n)
{
	return (void *)(uintptr_t)_fdt_mem_rsv(fdt, n);
}