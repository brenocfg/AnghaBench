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
 int /*<<< orphan*/  a_swap (int volatile*,int) ; 

__attribute__((used)) static inline void a_store(volatile int *p, int v)
{
#ifdef a_barrier
	a_barrier();
	*p = v;
	a_barrier();
#else
	a_swap(p, v);
#endif
}