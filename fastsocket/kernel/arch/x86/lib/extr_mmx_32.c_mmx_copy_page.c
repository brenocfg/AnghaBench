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

/* Variables and functions */
 int /*<<< orphan*/  fast_copy_page (void*,void*) ; 
 int /*<<< orphan*/  in_interrupt () ; 
 int /*<<< orphan*/  slow_copy_page (void*,void*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void mmx_copy_page(void *to, void *from)
{
	if (unlikely(in_interrupt()))
		slow_copy_page(to, from);
	else
		fast_copy_page(to, from);
}