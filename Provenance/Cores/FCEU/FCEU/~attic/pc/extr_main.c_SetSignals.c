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
 int SIGABRT ; 
 int SIGALRM ; 
 int SIGFPE ; 
 int SIGHUP ; 
 int SIGINT ; 
 int SIGKILL ; 
 int SIGPIPE ; 
 int SIGSEGV ; 
 int SIGTERM ; 
 int SIGUSR1 ; 
 int SIGUSR2 ; 
 int /*<<< orphan*/  signal (int,void (*) (int)) ; 

__attribute__((used)) static void SetSignals(void (*t)(int))
{
  int sigs[11]={SIGINT,SIGTERM,SIGHUP,SIGPIPE,SIGSEGV,SIGFPE,SIGKILL,SIGALRM,SIGABRT,SIGUSR1,SIGUSR2};
  int x;
  for(x=0;x<11;x++)
   signal(sigs[x],t);
}