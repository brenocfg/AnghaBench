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
 int /*<<< orphan*/  Cmd_AddCommand (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Cvar_Set (char*,char*) ; 
 int /*<<< orphan*/  IN_Init () ; 
 char* Sys_GetCurrentUser () ; 
 int /*<<< orphan*/  Sys_In_Restart_f ; 

void Sys_Init(void)
{
  Cmd_AddCommand ("in_restart", Sys_In_Restart_f);

#if defined __linux__
#if defined __i386__
  Cvar_Set( "arch", "linux i386" );
#elif defined __alpha__
  Cvar_Set( "arch", "linux alpha" );
#elif defined __sparc__
  Cvar_Set( "arch", "linux sparc" );
#elif defined __FreeBSD__

#if defined __i386__ // FreeBSD
  Cvar_Set( "arch", "freebsd i386" );
#elif defined __alpha__
  Cvar_Set( "arch", "freebsd alpha" );
#else
  Cvar_Set( "arch", "freebsd unknown" );
#endif // FreeBSD

#else
  Cvar_Set( "arch", "linux unknown" );
#endif
#elif defined __sun__
#if defined __i386__
  Cvar_Set( "arch", "solaris x86" );
#elif defined __sparc__
  Cvar_Set( "arch", "solaris sparc" );
#else
  Cvar_Set( "arch", "solaris unknown" );
#endif
#elif defined __sgi__
#if defined __mips__
  Cvar_Set( "arch", "sgi mips" );
#else
  Cvar_Set( "arch", "sgi unknown" );
#endif
#else
  Cvar_Set( "arch", "unknown" );
#endif

  Cvar_Set( "username", Sys_GetCurrentUser() );

  IN_Init();

}