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
struct lguest {TYPE_1__* pgdirs; int /*<<< orphan*/  kernel_address; } ;
struct TYPE_2__ {scalar_t__ pgdir; } ;

/* Variables and functions */
 unsigned int pgd_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_pgd (scalar_t__) ; 

__attribute__((used)) static void flush_user_mappings(struct lguest *lg, int idx)
{
	unsigned int i;
	/* Release every pgd entry up to the kernel's address. */
	for (i = 0; i < pgd_index(lg->kernel_address); i++)
		release_pgd(lg->pgdirs[idx].pgdir + i);
}