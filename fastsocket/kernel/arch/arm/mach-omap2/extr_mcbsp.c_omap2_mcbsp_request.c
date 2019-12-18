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
 unsigned int OMAP_MCBSP2 ; 
 scalar_t__ cpu_is_omap2420 () ; 
 int /*<<< orphan*/  omap2_mcbsp2_mux_setup () ; 

__attribute__((used)) static void omap2_mcbsp_request(unsigned int id)
{
	if (cpu_is_omap2420() && (id == OMAP_MCBSP2))
		omap2_mcbsp2_mux_setup();
}