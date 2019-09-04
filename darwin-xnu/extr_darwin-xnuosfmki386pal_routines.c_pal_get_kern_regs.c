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
typedef  int /*<<< orphan*/  x86_saved_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ *) ; 

void
pal_get_kern_regs( x86_saved_state_t *state )
{
	panic( "pal_get_kern_regs called. state %p\n", state );
}