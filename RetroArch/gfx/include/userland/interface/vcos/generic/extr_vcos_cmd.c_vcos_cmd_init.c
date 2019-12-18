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
struct TYPE_2__ {int /*<<< orphan*/ * cmd_entry; scalar_t__ num_cmd_alloc; scalar_t__ num_cmd_entries; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 TYPE_1__ cmd_globals ; 
 int /*<<< orphan*/  vcos_get_build_strings ; 
 int /*<<< orphan*/  vcos_keep_static_strings ; 
 int /*<<< orphan*/  vcos_mutex_create (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void vcos_cmd_init( void )
{
    vcos_mutex_create( &cmd_globals.lock, "vcos_cmd" );

    cmd_globals.num_cmd_entries = 0;
    cmd_globals.num_cmd_alloc = 0;
    cmd_globals.cmd_entry = NULL;

#ifdef HAVE_VCOS_VERSION
   vcos_keep_static_strings = vcos_get_build_strings;
#endif
}