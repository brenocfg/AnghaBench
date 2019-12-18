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
struct page {int dummy; } ;

/* Variables and functions */
 scalar_t__ is_vmalloc_addr (struct page**) ; 
 int /*<<< orphan*/  kfree (struct page**) ; 
 int /*<<< orphan*/  vfree (struct page**) ; 

__attribute__((used)) static void relay_free_page_array(struct page **array)
{
	if (is_vmalloc_addr(array))
		vfree(array);
	else
		kfree(array);
}