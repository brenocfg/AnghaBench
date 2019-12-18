#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * cmd_entry; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 TYPE_1__ cmd_globals ; 
 int /*<<< orphan*/  vcos_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_mutex_delete (int /*<<< orphan*/ *) ; 

void vcos_cmd_shutdown( void )
{
    vcos_mutex_delete( &cmd_globals.lock );

    vcos_free( cmd_globals.cmd_entry );
    cmd_globals.cmd_entry = NULL;
}