#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int page_alignment; } ;
struct TYPE_4__ {TYPE_1__ mem; } ;
struct radeon_bo {TYPE_2__ tbo; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int RADEON_GPU_PAGE_SIZE ; 

__attribute__((used)) static inline unsigned radeon_bo_gpu_page_alignment(struct radeon_bo *bo)
{
	return (bo->tbo.mem.page_alignment << PAGE_SHIFT) / RADEON_GPU_PAGE_SIZE;
}