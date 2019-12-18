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
typedef  int /*<<< orphan*/  ARTIFACT_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARTIFACT_mode ; 
 scalar_t__ Atari800_TV_NTSC ; 
 scalar_t__ Atari800_tv_mode ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UpdateMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mode_ntsc ; 
 int /*<<< orphan*/  mode_pal ; 

void ARTIFACT_Set(ARTIFACT_t mode)
{
	ARTIFACT_t old_effect = ARTIFACT_mode;
	ARTIFACT_mode = mode;
	if (Atari800_tv_mode == Atari800_TV_NTSC)
		mode_ntsc = mode;
	else /* Atari800_tv_mode == Atari800_TV_PAL */
		mode_pal = mode;
	UpdateMode(old_effect, TRUE);
}