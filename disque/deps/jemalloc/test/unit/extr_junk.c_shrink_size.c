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
 size_t nallocx (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
shrink_size(size_t size)
{
	size_t shrink_size;

	for (shrink_size = size - 1; nallocx(shrink_size, 0) == size;
	    shrink_size--)
		; /* Do nothing. */

	return (shrink_size);
}