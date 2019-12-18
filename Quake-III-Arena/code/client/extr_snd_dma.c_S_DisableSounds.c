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
 int /*<<< orphan*/  S_StopAllSounds () ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  s_soundMuted ; 

void S_DisableSounds( void ) {
	S_StopAllSounds();
	s_soundMuted = qtrue;
}