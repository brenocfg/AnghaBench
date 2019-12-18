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
 int /*<<< orphan*/  quit_event ; 
 int /*<<< orphan*/  vcos_event_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_log_info (char*) ; 

__attribute__((used)) static void control_c( int signum )
{
    (void)signum;

    vcos_log_info( "Shutting down..." );

    vcos_event_signal( &quit_event );
}