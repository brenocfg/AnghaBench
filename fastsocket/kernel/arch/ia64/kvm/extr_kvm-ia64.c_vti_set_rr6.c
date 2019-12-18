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
 int /*<<< orphan*/  RR6 ; 
 int /*<<< orphan*/  ia64_set_rr (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  ia64_srlz_i () ; 

__attribute__((used)) static inline void vti_set_rr6(unsigned long rr6)
{
	ia64_set_rr(RR6, rr6);
	ia64_srlz_i();
}