#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  va_list ;
struct TYPE_5__ {char* result_size; char* result_ptr; int result_buf; int use_log; } ;
typedef  TYPE_1__ VCOS_CMD_PARAM_T ;
struct TYPE_6__ {int /*<<< orphan*/ * log_category; } ;

/* Variables and functions */
 TYPE_4__ cmd_globals ; 
 int /*<<< orphan*/  cmd_log_results (TYPE_1__*) ; 
 int vcos_vsnprintf (char*,int,char const*,int /*<<< orphan*/ ) ; 

void vcos_cmd_vprintf( VCOS_CMD_PARAM_T *param, const char *fmt, va_list args )
{
    int     bytes_written;
    int     bytes_remaining;

    bytes_remaining = (int)(param->result_size - ( param->result_ptr - param->result_buf ));

    bytes_written = vcos_vsnprintf( param->result_ptr, bytes_remaining, fmt, args );

    if ( cmd_globals.log_category != NULL )
    {
        /* We're going to log each line as we encounter it. If the buffer
         * doesn't end in a newline, then we'll wait for one first.
         */

        if ( (( bytes_written + 1 ) >= bytes_remaining )
        ||   ( param->result_ptr[ bytes_written - 1 ] == '\n' ))
        {
            cmd_log_results( param );
        }
        else
        {
            param->result_ptr += bytes_written;
        }
    }
    else
    {
        if (( bytes_written + 1 ) >= bytes_remaining )
        {
            /* Output doesn't fit - switch over to logging */

            param->use_log = 1;

            *param->result_ptr = '\0';  /* Zap the partial line that didn't fit above. */

            cmd_log_results( param );   /* resets result_ptr */

            bytes_written = vcos_vsnprintf( param->result_ptr, bytes_remaining, fmt, args );
        }
        param->result_ptr += bytes_written;
    }
}