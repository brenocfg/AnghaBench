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
 int /*<<< orphan*/  FS_FCloseFile (scalar_t__) ; 
 int /*<<< orphan*/  Sys_EndStreamedFile (scalar_t__) ; 
 scalar_t__ s_backgroundFile ; 
 scalar_t__ s_rawend ; 

void S_StopBackgroundTrack( void ) {
	if ( !s_backgroundFile ) {
		return;
	}
	Sys_EndStreamedFile( s_backgroundFile );
	FS_FCloseFile( s_backgroundFile );
	s_backgroundFile = 0;
	s_rawend = 0;
}