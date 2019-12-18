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
struct vml_par {int /*<<< orphan*/  vdc_mem_size; int /*<<< orphan*/  vdc_mem_base; int /*<<< orphan*/  vdc_mem; int /*<<< orphan*/  gpu_mem_size; int /*<<< orphan*/  gpu_mem_base; int /*<<< orphan*/  gpu_mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vmlfb_disable_mmio(struct vml_par *par)
{
	iounmap(par->gpu_mem);
	release_mem_region(par->gpu_mem_base, par->gpu_mem_size);
	iounmap(par->vdc_mem);
	release_mem_region(par->vdc_mem_base, par->vdc_mem_size);
}