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
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  grow1 (int) ; 

void
grow(int frame)
{
	/*
	 * Create a ridiculously large stack - enough to push us over
	 * the default setting of 'dtrace_ustackdepth_max' (2048).
	 */
	if (frame >= 2048)
		for (;;)
			getpid();

	grow1(++frame);
}