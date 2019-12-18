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
typedef  scalar_t__ sfxHandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Printf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  S_COLOR_YELLOW ; 
 int /*<<< orphan*/  S_StartSound (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  listener_number ; 
 scalar_t__ s_numSfx ; 
 scalar_t__ s_soundMuted ; 
 int /*<<< orphan*/  s_soundStarted ; 

void S_StartLocalSound( sfxHandle_t sfxHandle, int channelNum ) {
	if ( !s_soundStarted || s_soundMuted ) {
		return;
	}

	if ( sfxHandle < 0 || sfxHandle >= s_numSfx ) {
		Com_Printf( S_COLOR_YELLOW, "S_StartLocalSound: handle %i out of range\n", sfxHandle );
		return;
	}

	S_StartSound (NULL, listener_number, channelNum, sfxHandle );
}