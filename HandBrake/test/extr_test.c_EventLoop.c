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
struct timeval {int tv_usec; scalar_t__ tv_sec; } ;
typedef  int /*<<< orphan*/  hb_handle_t ;
typedef  int /*<<< orphan*/  hb_dict_t ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  FD_SET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HB_ERROR_CANCELED ; 
 int /*<<< orphan*/  HandleEvents (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ STDIN_FILENO ; 
 int /*<<< orphan*/  ShowCommands () ; 
 int _getch () ; 
 scalar_t__ _kbhit () ; 
 int die ; 
 int /*<<< orphan*/  done_error ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hb_pause (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_resume (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_snooze (int) ; 
 int /*<<< orphan*/  hb_system_sleep_allow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_system_sleep_prevent (int /*<<< orphan*/ *) ; 
 scalar_t__ job_running ; 
 scalar_t__ read (scalar_t__,char*,int) ; 
 int select (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ work_done ; 

void EventLoop(hb_handle_t *h, hb_dict_t *preset_dict)
{
    /* Wait... */
    work_done = 0;
    while (!die && !work_done)
    {
#if defined( __MINGW32__ )
        if( _kbhit() ) {
            switch( _getch() )
            {
                case 0x03: /* ctrl-c */
                case 'q':
                    fprintf( stdout, "\nEncoding Quit by user command\n" );
                    done_error = HB_ERROR_CANCELED;
                    die = 1;
                    break;
                case 'p':
                    fprintf(stdout,
                            "\nEncoding Paused by user command, 'r' to resume\n");
                    hb_pause(h);
                    hb_system_sleep_allow(h);
                    break;
                case 'r':
                    hb_system_sleep_prevent(h);
                    hb_resume(h);
                    break;
                case 'h':
                    ShowCommands();
                    break;
            }
        }
#else
        fd_set         fds;
        struct timeval tv;
        int            ret;
        char           buf[257];

        tv.tv_sec  = 0;
        tv.tv_usec = 100000;

        FD_ZERO( &fds );
        FD_SET( STDIN_FILENO, &fds );
        ret = select( STDIN_FILENO + 1, &fds, NULL, NULL, &tv );

        if( ret > 0 )
        {
            int size = 0;

            while( size < 256 &&
                   read( STDIN_FILENO, &buf[size], 1 ) > 0 )
            {
                if( buf[size] == '\n' )
                {
                    break;
                }
                size++;
            }

            if( size >= 256 || buf[size] == '\n' )
            {
                switch( buf[0] )
                {
                    case 'q':
                        fprintf( stdout, "\nEncoding Quit by user command\n" );
                        done_error = HB_ERROR_CANCELED;
                        die = 1;
                        break;
                    case 'p':
                        fprintf(stdout,
                                "\nEncoding Paused by user command, 'r' to resume\n");
                        hb_pause(h);
                        hb_system_sleep_allow(h);
                        break;
                    case 'r':
                        hb_system_sleep_prevent(h);
                        hb_resume(h);
                        break;
                    case 'h':
                        ShowCommands();
                        break;
                }
            }
        }
#endif
        hb_snooze(200);

        HandleEvents( h, preset_dict );
    }
    job_running = 0;
}