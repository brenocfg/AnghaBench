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
 int /*<<< orphan*/  DriverKill () ; 
#define  SIGABRT 138 
#define  SIGALRM 137 
#define  SIGBUS 136 
#define  SIGFPE 135 
#define  SIGHUP 134 
#define  SIGINT 133 
#define  SIGPIPE 132 
#define  SIGSEGV 131 
#define  SIGTERM 130 
#define  SIGUSR1 129 
#define  SIGUSR2 128 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void CloseStuff(int signum)
{
	DriverKill();
        printf("\nSignal %d has been caught and dealt with...\n",signum);
        switch(signum)
        {
         case SIGINT:printf("How DARE you interrupt me!\n");break;
         case SIGTERM:printf("MUST TERMINATE ALL HUMANS\n");break;
         case SIGHUP:printf("Reach out and hang-up on someone.\n");break;
         case SIGPIPE:printf("The pipe has broken!  Better watch out for floods...\n");break;
         case SIGSEGV:printf("Iyeeeeeeeee!!!  A segmentation fault has occurred.  Have a fluffy day.\n");break;
	 /* So much SIGBUS evil. */
	 #ifdef SIGBUS
	 #if(SIGBUS!=SIGSEGV)
         case SIGBUS:printf("I told you to be nice to the driver.\n");break;
	 #endif
	 #endif
         case SIGFPE:printf("Those darn floating points.  Ne'er know when they'll bite!\n");break;
         case SIGALRM:printf("Don't throw your clock at the meowing cats!\n");break;
         case SIGABRT:printf("Abort, Retry, Ignore, Fail?\n");break;
         case SIGUSR1:
         case SIGUSR2:printf("Killing your processes is not nice.\n");break;
        }
        exit(1);
}