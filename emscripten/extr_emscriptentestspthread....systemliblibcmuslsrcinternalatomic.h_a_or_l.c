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
 int /*<<< orphan*/  a_or (void volatile*,long) ; 
 int /*<<< orphan*/  a_or_64 (void volatile*,long) ; 

__attribute__((used)) static inline void a_or_l(volatile void *p, long v)
{
	if (sizeof(long) == sizeof(int)) a_or(p, v);
	else a_or_64(p, v);
}