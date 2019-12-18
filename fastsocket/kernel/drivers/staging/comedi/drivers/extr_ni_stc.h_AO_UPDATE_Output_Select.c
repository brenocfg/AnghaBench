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
typedef  enum ao_update_output_selection { ____Placeholder_ao_update_output_selection } ao_update_output_selection ;

/* Variables and functions */

__attribute__((used)) static unsigned AO_UPDATE_Output_Select(enum ao_update_output_selection
					selection)
{
	return selection & 0x3;
}