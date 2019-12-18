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
 long SBUS_MMAP_EMPTY ; 

__attribute__((used)) static unsigned long sbusfb_mmapsize(long size, unsigned long fbsize)
{
	if (size == SBUS_MMAP_EMPTY) return 0;
	if (size >= 0) return size;
	return fbsize * (-size);
}