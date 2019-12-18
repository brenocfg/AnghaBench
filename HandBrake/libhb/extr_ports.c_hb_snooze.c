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
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  snooze (int) ; 
 int /*<<< orphan*/  usleep (int) ; 

void hb_snooze( int delay )
{
    if( delay < 1 )
    {
        return;
    }
#if defined( SYS_BEOS )
    snooze( 1000 * delay );
#elif defined( SYS_DARWIN ) || defined( SYS_LINUX ) || defined( SYS_FREEBSD) || defined( SYS_SunOS )
    usleep( 1000 * delay );
#elif defined( SYS_CYGWIN ) || defined( SYS_MINGW )
    Sleep( delay );
#endif
}