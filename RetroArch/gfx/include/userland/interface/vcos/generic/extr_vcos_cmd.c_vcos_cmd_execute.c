#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VCOS_STATUS_T ;
struct TYPE_6__ {int argc; char** argv; char** argv_orig; size_t result_size; char* result_ptr; char* result_buf; scalar_t__ use_log; } ;
typedef  TYPE_1__ VCOS_CMD_PARAM_T ;
struct TYPE_7__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ * log_category; int /*<<< orphan*/  cmd_entry; int /*<<< orphan*/  initialized; } ;

/* Variables and functions */
 int /*<<< orphan*/  VCOS_EINVAL ; 
 TYPE_5__ cmd_globals ; 
 int /*<<< orphan*/  cmd_log_results (TYPE_1__*) ; 
 int /*<<< orphan*/  execute_cmd (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_cmd_init ; 
 int /*<<< orphan*/  vcos_cmd_printf (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  vcos_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_snprintf (char*,size_t,char*) ; 

VCOS_STATUS_T vcos_cmd_execute( int argc, char **argv, size_t result_size, char *result_buf )
{
    VCOS_STATUS_T       rc = VCOS_EINVAL;
    VCOS_CMD_PARAM_T    param;

    vcos_once( &cmd_globals.initialized, vcos_cmd_init );

    param.argc = argc;
    param.argv = param.argv_orig = argv;

    param.use_log = 0;
    param.result_size = result_size;
    param.result_ptr = result_buf;
    param.result_buf = result_buf;

	result_buf[0] = '\0';

    vcos_mutex_lock( &cmd_globals.lock );

    rc = execute_cmd( &param, cmd_globals.cmd_entry );

    if ( param.use_log )
    {
        cmd_log_results( &param );
        vcos_snprintf( result_buf, result_size, "results logged" );
    }
    else
    if ( cmd_globals.log_category != NULL )
    {
        if ( result_buf[0] != '\0' )
        {
            /* There is a partial line still buffered. */

            vcos_cmd_printf( &param, "\n" );
        }
    }

    vcos_mutex_unlock( &cmd_globals.lock );

    return rc;
}