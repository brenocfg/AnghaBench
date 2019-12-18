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
 int /*<<< orphan*/  gru_flush_cache (void*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void start_instruction(void *h)
{
	unsigned long *w0 = h;

	wmb();		/* setting CMD/STATUS bits must be last */
	*w0 = *w0 | 0x20001;
	gru_flush_cache(h);
}