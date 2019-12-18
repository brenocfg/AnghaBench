#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  descr; int /*<<< orphan*/ * args; int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ VCOS_CMD_T ;
typedef  int /*<<< orphan*/  VCOS_CMD_PARAM_T ;

/* Variables and functions */
 int /*<<< orphan*/  print_argument_prefix (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_cmd_printf (int /*<<< orphan*/ *,char*,...) ; 
 int vcos_strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void usage( VCOS_CMD_PARAM_T *param, VCOS_CMD_T *cmd_entry )
{
    int         cmd_idx;
    int         nameWidth = 0;
    int         argsWidth = 0;
    VCOS_CMD_T *scan_entry;

    vcos_cmd_printf( param, "Usage: " );
    print_argument_prefix( param );
    vcos_cmd_printf( param, "command [args ...]\n" );
    vcos_cmd_printf( param, "\n" );
    vcos_cmd_printf( param, "Where command is one of the following:\n" );

    for ( cmd_idx = 0; cmd_entry[cmd_idx].name != NULL; cmd_idx++ )
    {
        int aw;
        int nw;

        scan_entry = &cmd_entry[cmd_idx];

        nw = vcos_strlen( scan_entry->name );
        aw = vcos_strlen( scan_entry->args );

        if ( nw > nameWidth )
        {
            nameWidth = nw;
        }
        if ( aw > argsWidth )
        {
            argsWidth = aw;
        }
    }

    for ( cmd_idx = 0; cmd_entry[cmd_idx].name != NULL; cmd_idx++ )
    {
        scan_entry = &cmd_entry[cmd_idx];

        vcos_cmd_printf( param, "  %-*s %-*s - %s\n",
                    nameWidth, scan_entry->name,
                    argsWidth, scan_entry->args,
                    scan_entry->descr );
    }
}