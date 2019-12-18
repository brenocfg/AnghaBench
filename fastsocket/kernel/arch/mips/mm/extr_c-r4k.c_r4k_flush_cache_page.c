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
struct vm_area_struct {int dummy; } ;
struct flush_cache_page_args {unsigned long addr; unsigned long pfn; struct vm_area_struct* vma; } ;

/* Variables and functions */
 int /*<<< orphan*/  local_r4k_flush_cache_page ; 
 int /*<<< orphan*/  r4k_on_each_cpu (int /*<<< orphan*/ ,struct flush_cache_page_args*,int) ; 

__attribute__((used)) static void r4k_flush_cache_page(struct vm_area_struct *vma,
	unsigned long addr, unsigned long pfn)
{
	struct flush_cache_page_args args;

	args.vma = vma;
	args.addr = addr;
	args.pfn = pfn;

	r4k_on_each_cpu(local_r4k_flush_cache_page, &args, 1);
}