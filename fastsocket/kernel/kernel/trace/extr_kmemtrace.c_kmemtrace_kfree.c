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
 int /*<<< orphan*/  KMEMTRACE_TYPE_KMALLOC ; 
 int /*<<< orphan*/  kmemtrace_free (int /*<<< orphan*/ ,unsigned long,void const*) ; 

__attribute__((used)) static void kmemtrace_kfree(unsigned long call_site, const void *ptr)
{
	kmemtrace_free(KMEMTRACE_TYPE_KMALLOC, call_site, ptr);
}