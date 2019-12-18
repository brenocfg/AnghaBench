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
 int /*<<< orphan*/  drc_cmn_cleanup () ; 

void PicoSVPInit(void)
{
#ifdef _SVP_DRC
	// this is to unmap tcache and make
	// mem available for large ROMs, MCD, etc.
	drc_cmn_cleanup();
#endif
}