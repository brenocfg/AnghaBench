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
struct b43_rfatt {scalar_t__ att; scalar_t__ with_padmix; } ;

/* Variables and functions */

__attribute__((used)) static inline bool b43_compare_rfatt(const struct b43_rfatt *a,
				     const struct b43_rfatt *b)
{
	return ((a->att == b->att) &&
		(a->with_padmix == b->with_padmix));
}