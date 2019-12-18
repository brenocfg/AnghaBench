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
struct dpages {scalar_t__ context_u; int /*<<< orphan*/  context_ptr; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 

__attribute__((used)) static void vm_next_page(struct dpages *dp)
{
	dp->context_ptr += PAGE_SIZE - dp->context_u;
	dp->context_u = 0;
}