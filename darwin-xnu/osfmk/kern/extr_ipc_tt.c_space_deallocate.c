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
typedef  scalar_t__ ipc_space_t ;

/* Variables and functions */
 scalar_t__ IS_NULL ; 
 int /*<<< orphan*/  is_release (scalar_t__) ; 

void
space_deallocate(
	ipc_space_t	space)
{
	if (space != IS_NULL)
		is_release(space);
}