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
struct TYPE_3__ {struct TYPE_3__* prev; void* arg; int /*<<< orphan*/  routine; } ;
typedef  TYPE_1__ pte_cleanup_t ;
typedef  int /*<<< orphan*/  pte_cleanup_callback_t ;

/* Variables and functions */
 int /*<<< orphan*/  pte_cleanupKey ; 
 scalar_t__ pthread_getspecific (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_setspecific (int /*<<< orphan*/ ,void*) ; 

void
pte_push_cleanup (pte_cleanup_t * cleanup,
      pte_cleanup_callback_t routine, void *arg)
   /*
    * ------------------------------------------------------
    * DOCPUBLIC
    *      This function pushes a new cleanup handler onto the thread's stack
    *      of cleanup handlers. Each cleanup handler pushed onto the stack is
    *      popped and invoked with the argument 'arg' when
    *              a) the thread exits by calling 'pthread_exit',
    *              b) when the thread acts on a cancellation request,
    *              c) or when the thread calls pthread_cleanup_pop with a nonzero
    *                 'execute' argument
    *
    * PARAMETERS
    *      cleanup
    *              a pointer to an instance of pthread_cleanup_t,
    *
    *      routine
    *              pointer to a cleanup handler,
    *
    *      arg
    *              parameter to be passed to the cleanup handler
    *
    *
    * DESCRIPTION
    *      This function pushes a new cleanup handler onto the thread's stack
    *      of cleanup handlers. Each cleanup handler pushed onto the stack is
    *      popped and invoked with the argument 'arg' when
    *              a) the thread exits by calling 'pthread_exit',
    *              b) when the thread acts on a cancellation request,
    *              c) or when the thrad calls pthread_cleanup_pop with a nonzero
    *                 'execute' argument
    *      NOTE: pthread_push_cleanup, pte_pop_cleanup must be paired
    *                in the same lexical scope.
    *
    * RESULTS
    *              pthread_cleanup_t *
    *                              pointer to the previous cleanup
    *
    * ------------------------------------------------------
    */
{
   cleanup->routine = routine;
   cleanup->arg = arg;

   cleanup->prev = (pte_cleanup_t *) pthread_getspecific (pte_cleanupKey);

   pthread_setspecific (pte_cleanupKey, (void *) cleanup);
}