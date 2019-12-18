#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int ss_size; scalar_t__ ss_sp; } ;
struct TYPE_6__ {TYPE_1__ uc_stack; int /*<<< orphan*/ * uc_link; } ;
typedef  TYPE_2__ ucontext_t ;
typedef  int /*<<< orphan*/  cothread_t ;

/* Variables and functions */
 int /*<<< orphan*/  co_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  co_primary ; 
 int /*<<< orphan*/ * co_running ; 
 int /*<<< orphan*/  getcontext (TYPE_2__*) ; 
 int /*<<< orphan*/  makecontext (TYPE_2__*,void (*) (),int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (unsigned int) ; 

cothread_t co_create(unsigned int heapsize, void (*coentry)(void))
{
   if (!co_running)
      co_running = &co_primary;
   ucontext_t *thread = (ucontext_t*)malloc(sizeof(ucontext_t));

   if(thread)
   {
      if((!getcontext(thread) && !(thread->uc_stack.ss_sp = 0)) && (thread->uc_stack.ss_sp = malloc(heapsize)))
      {
         thread->uc_link = co_running;
         thread->uc_stack.ss_size = heapsize;
         makecontext(thread, coentry, 0);
      }
      else
      {
         co_delete((cothread_t)thread);
         thread = 0;
      }
   }
   return (cothread_t)thread;
}