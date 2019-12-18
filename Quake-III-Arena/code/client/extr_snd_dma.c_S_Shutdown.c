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
 int /*<<< orphan*/  Cmd_RemoveCommand (char*) ; 
 int /*<<< orphan*/  SNDDMA_Shutdown () ; 
 scalar_t__ s_soundStarted ; 

void S_Shutdown( void ) {
	if ( !s_soundStarted ) {
		return;
	}

	SNDDMA_Shutdown();

	s_soundStarted = 0;

    Cmd_RemoveCommand("play");
	Cmd_RemoveCommand("music");
	Cmd_RemoveCommand("stopsound");
	Cmd_RemoveCommand("soundlist");
	Cmd_RemoveCommand("soundinfo");
}