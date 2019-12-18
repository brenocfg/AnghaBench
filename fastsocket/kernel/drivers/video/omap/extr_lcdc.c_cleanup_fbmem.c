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
struct TYPE_2__ {scalar_t__ fbmem_allocated; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_fbmem () ; 
 TYPE_1__ lcdc ; 
 int /*<<< orphan*/  unmap_kern () ; 

__attribute__((used)) static void cleanup_fbmem(void)
{
	if (lcdc.fbmem_allocated)
		free_fbmem();
	else
		unmap_kern();
}