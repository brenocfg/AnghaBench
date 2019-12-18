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
 int /*<<< orphan*/  PLDI2CSTS ; 
 int PLDI2CSTS_NOACK ; 
 int ar_inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 

__attribute__((used)) static inline void wait_acknowledge(void)
{
	int i;

	for (i = 0; i < 1000; i++)
		cpu_relax();
	while (ar_inl(PLDI2CSTS) & PLDI2CSTS_NOACK)
		cpu_relax();
}