#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct TYPE_3__ {int num_pages; scalar_t__ start; } ;
typedef  TYPE_1__ kern_memdesc_t ;

/* Variables and functions */
 int EFI_PAGE_SHIFT ; 

__attribute__((used)) static inline u64
kmd_end(kern_memdesc_t *kmd)
{
	return (kmd->start + (kmd->num_pages << EFI_PAGE_SHIFT));
}