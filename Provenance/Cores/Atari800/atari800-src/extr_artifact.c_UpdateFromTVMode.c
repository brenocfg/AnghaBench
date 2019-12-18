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
 int /*<<< orphan*/  ARTIFACT_mode ; 
 int Atari800_TV_NTSC ; 
 int /*<<< orphan*/  mode_ntsc ; 
 int /*<<< orphan*/  mode_pal ; 

__attribute__((used)) static void UpdateFromTVMode(int tv_mode)
{
	if (tv_mode == Atari800_TV_NTSC)
		ARTIFACT_mode = mode_ntsc;
	else /* tv_mode == Atari800_TV_PAL */
		ARTIFACT_mode = mode_pal;
}