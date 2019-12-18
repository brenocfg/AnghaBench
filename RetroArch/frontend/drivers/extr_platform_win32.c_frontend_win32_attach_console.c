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
 int /*<<< orphan*/  ATTACH_PARENT_PROCESS ; 
 int /*<<< orphan*/  AllocConsole () ; 
 int /*<<< orphan*/  AttachConsole (int /*<<< orphan*/ ) ; 
 scalar_t__ FILE_TYPE_UNKNOWN ; 
 scalar_t__ GetFileType (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetStdHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STD_ERROR_HANDLE ; 
 int /*<<< orphan*/  STD_OUTPUT_HANDLE ; 
 int /*<<< orphan*/  SetConsoleTitle (char*) ; 
 int console_needs_free ; 
 int /*<<< orphan*/  freopen (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void frontend_win32_attach_console(void)
{
#ifdef _WIN32
#ifdef _WIN32_WINNT_WINXP
   /* msys will start the process with FILE_TYPE_PIPE connected.
    *   cmd will start the process with FILE_TYPE_UNKNOWN connected
    *   (since this is subsystem windows application
    * ... UNLESS stdout/stderr were redirected (then FILE_TYPE_DISK
    * will be connected most likely)
    * explorer will start the process with NOTHING connected.
    *
    * Now, let's not reconnect anything that's already connected.
    * If any are disconnected, open a console, and connect to them.
    * In case we're launched from msys or cmd, try attaching to the
    * parent process console first.
    *
    * Take care to leave a record of what we did, so we can
    * undo it precisely.
    */

   bool need_stdout = (GetFileType(GetStdHandle(STD_OUTPUT_HANDLE))
         == FILE_TYPE_UNKNOWN);
   bool need_stderr = (GetFileType(GetStdHandle(STD_ERROR_HANDLE))
         == FILE_TYPE_UNKNOWN);

   if(need_stdout || need_stderr)
   {
      if(!AttachConsole( ATTACH_PARENT_PROCESS))
         AllocConsole();

      SetConsoleTitle("Log Console");

      if(need_stdout) freopen( "CONOUT$", "w", stdout );
      if(need_stderr) freopen( "CONOUT$", "w", stderr );

      console_needs_free = true;
   }

#endif
#endif
}