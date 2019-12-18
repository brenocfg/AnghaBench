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
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int ni_m_series_max_pfi_channel ; 

__attribute__((used)) static inline unsigned NI_M_Series_PFI_Clock(unsigned n)
{
	BUG_ON(n > ni_m_series_max_pfi_channel);
	if (n < 10)
		return 1 + n;
	else
		return 0xb + n;
}