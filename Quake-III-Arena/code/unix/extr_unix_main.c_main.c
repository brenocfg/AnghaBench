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
typedef  int /*<<< orphan*/  sysEvent_t ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Frame () ; 
 int /*<<< orphan*/  Com_Init (char*) ; 
 int FNDELAY ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  InitSig () ; 
 int MAX_MSGLEN ; 
 int MAX_QUED_EVENTS ; 
 int /*<<< orphan*/  NET_Init () ; 
 int /*<<< orphan*/  Sys_ConfigureFPU () ; 
 int /*<<< orphan*/  Sys_ConsoleInputInit () ; 
 int /*<<< orphan*/  Sys_ParseArgs (int,char**) ; 
 int /*<<< orphan*/ * eventQue ; 
 int fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  geteuid () ; 
 int /*<<< orphan*/  getuid () ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  saved_euid ; 
 int /*<<< orphan*/  seteuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/ * sys_packetReceived ; 

int main ( int argc, char* argv[] )
{
  // int 	oldtime, newtime; // bk001204 - unused
  int   len, i;
  char  *cmdline;
  void Sys_SetDefaultCDPath(const char *path);

  // go back to real user for config loads
  saved_euid = geteuid();
  seteuid(getuid());

  Sys_ParseArgs( argc, argv );  // bk010104 - added this for support

  Sys_SetDefaultCDPath(argv[0]);

  // merge the command line, this is kinda silly
  for (len = 1, i = 1; i < argc; i++)
    len += strlen(argv[i]) + 1;
  cmdline = malloc(len);
  *cmdline = 0;
  for (i = 1; i < argc; i++)
  {
    if (i > 1)
      strcat(cmdline, " ");
    strcat(cmdline, argv[i]);
  }

  // bk000306 - clear queues
  memset( &eventQue[0], 0, MAX_QUED_EVENTS*sizeof(sysEvent_t) ); 
  memset( &sys_packetReceived[0], 0, MAX_MSGLEN*sizeof(byte) );

  Com_Init(cmdline);
  NET_Init();

  Sys_ConsoleInputInit();

  fcntl(0, F_SETFL, fcntl (0, F_GETFL, 0) | FNDELAY);
	
#ifdef DEDICATED
	// init here for dedicated, as we don't have GLimp_Init
	InitSig();
#endif

  while (1)
  {
#ifdef __linux__
    Sys_ConfigureFPU();
#endif
    Com_Frame ();
  }
}