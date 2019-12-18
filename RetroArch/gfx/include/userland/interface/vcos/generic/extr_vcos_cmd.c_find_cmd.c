#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ VCOS_CMD_T ;

/* Variables and functions */
 scalar_t__ vcos_strcmp (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static VCOS_CMD_T *find_cmd( VCOS_CMD_T *cmd_entry, const char *name )
{
    VCOS_CMD_T   *scan_entry = cmd_entry;

    while ( scan_entry->name != NULL )
    {
        if ( vcos_strcmp( scan_entry->name, name ) == 0 )
        {
            return scan_entry;
        }
        scan_entry++;
    }

    return NULL;
}