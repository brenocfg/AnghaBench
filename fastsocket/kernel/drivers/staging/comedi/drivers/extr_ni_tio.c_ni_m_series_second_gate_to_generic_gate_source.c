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

__attribute__((used)) static unsigned ni_m_series_second_gate_to_generic_gate_source(unsigned
							       ni_m_series_gate_select)
{
	/*FIXME: the second gate sources for the m series are undocumented, so we just return
	 * the raw bits for now. */
	switch (ni_m_series_gate_select) {
	default:
		return ni_m_series_gate_select;
		break;
	}
	return 0;
}