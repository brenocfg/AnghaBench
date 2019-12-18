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
 int /*<<< orphan*/ * uu_panic_format ; 
 scalar_t__ uu_panic_thread ; 
 int /*<<< orphan*/  uu_release () ; 

__attribute__((used)) static void
uu_release_child(void)
{
	uu_panic_format = NULL;
	uu_panic_thread = 0;

	uu_release();
}