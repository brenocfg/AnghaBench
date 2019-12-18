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
 int /*<<< orphan*/  CG_S_STARTBACKGROUNDTRACK ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ,char const*,char const*) ; 

void	trap_S_StartBackgroundTrack( const char *intro, const char *loop ) {
	syscall( CG_S_STARTBACKGROUNDTRACK, intro, loop );
}