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
typedef  int /*<<< orphan*/ * SFG_Proc ;

/* Variables and functions */

SFG_Proc fghGetProcAddress( const char *procName )
{
#if TARGET_HOST_MS_WINDOWS
    return (SFG_Proc)wglGetProcAddress( ( LPCSTR )procName );
#elif TARGET_HOST_POSIX_X11 && defined( GLX_ARB_get_proc_address )
    return (SFG_Proc)glXGetProcAddressARB( ( const GLubyte * )procName );
#else
    return NULL;
#endif
}