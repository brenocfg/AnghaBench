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
 int FALSE ; 
 int /*<<< orphan*/  PBI_XLD_v_enabled ; 
 int TRUE ; 
 int /*<<< orphan*/  VOICEBOX_enabled ; 

__attribute__((used)) static int votraxsnd_enabled(void)
{
	if (
#ifdef VOICEBOX
		!VOICEBOX_enabled &&
#endif
#ifdef PBI_XLD
		!PBI_XLD_v_enabled &&

#endif
		1) return FALSE;
	else return TRUE;
}