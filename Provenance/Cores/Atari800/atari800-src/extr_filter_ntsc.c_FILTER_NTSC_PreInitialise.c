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
 int /*<<< orphan*/  FILTER_NTSC_setup ; 
 int /*<<< orphan*/  atari_ntsc_composite ; 

void FILTER_NTSC_PreInitialise(void)
{
	/* atari_ntsc_composite acts as the default setup. */
	FILTER_NTSC_setup = atari_ntsc_composite;
}