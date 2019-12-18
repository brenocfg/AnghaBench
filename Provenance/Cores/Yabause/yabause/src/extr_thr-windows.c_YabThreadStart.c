#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int running; void (* func ) (void*) ;int /*<<< orphan*/ * thd; void* arg; int /*<<< orphan*/ * cond; int /*<<< orphan*/  mutex; } ;
typedef  int /*<<< orphan*/  LPTHREAD_START_ROUTINE ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateThread (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  InitializeCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TlsAlloc () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  hnd_key ; 
 int hnd_key_once ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  stderr ; 
 TYPE_1__* thread_handle ; 
 scalar_t__ wrapper ; 

int YabThreadStart(unsigned int id, void (*func)(void *), void *arg) 
{ 
   if (!hnd_key_once)
   {
      hnd_key=TlsAlloc();
      hnd_key_once = 1;
   }

   if (thread_handle[id].running)
   {
      fprintf(stderr, "YabThreadStart: thread %u is already started!\n", id);
      return -1;
   }
   
   // Create CS and condition variable for thread
   InitializeCriticalSection(&thread_handle[id].mutex);
   if ((thread_handle[id].cond = CreateEvent(NULL, FALSE, FALSE, NULL)) == NULL)
   {
      perror("CreateEvent");
   	  return -1;
   }

   thread_handle[id].func = func;
   thread_handle[id].arg = arg;

   if ((thread_handle[id].thd = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)wrapper, &thread_handle[id], 0, NULL)) == NULL)
   {
      perror("CreateThread");
      return -1;
   }
   
   thread_handle[id].running = 1;

   return 0; 
}