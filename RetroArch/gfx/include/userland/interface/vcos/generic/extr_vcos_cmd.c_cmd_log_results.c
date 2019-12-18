#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* result_buf; char* result_ptr; } ;
typedef  TYPE_1__ VCOS_CMD_PARAM_T ;
struct TYPE_5__ {int /*<<< orphan*/ * log_category; } ;

/* Variables and functions */
 int /*<<< orphan*/  VCOS_LOG_INFO ; 
 TYPE_3__ cmd_globals ; 
 scalar_t__ vcos_is_log_enabled (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_log_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  vcos_log_info (char*,char*) ; 

__attribute__((used)) static void cmd_log_results( VCOS_CMD_PARAM_T *param )
{
    char    *start;
    char    *end;

    start = end = param->result_buf;

    while ( *start != '\0' )
    {
        while (( *end != '\0' ) && ( *end != '\n' ))
            end++;

        if ( *end == '\n' )
        {
            *end++ = '\0';
        }

        if ( cmd_globals.log_category != NULL )
        {
            if ( vcos_is_log_enabled( cmd_globals.log_category, VCOS_LOG_INFO ))
            {
                vcos_log_impl( cmd_globals.log_category, VCOS_LOG_INFO, "%s", start );
            }
        }
        else
        {
            vcos_log_info( "%s", start );
        }

        start = end;
    }

    /* Since we logged the buffer, reset the pointer back to the beginning. */

    param->result_ptr = param->result_buf;
    param->result_buf[0] = '\0';
}