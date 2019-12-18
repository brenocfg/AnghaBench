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
struct revectored_struct {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int is_revectored(int nr, struct revectored_struct *bitmap)
{
	__asm__ __volatile__("btl %2,%1\n\tsbbl %0,%0"
		:"=r" (nr)
		:"m" (*bitmap), "r" (nr));
	return nr;
}