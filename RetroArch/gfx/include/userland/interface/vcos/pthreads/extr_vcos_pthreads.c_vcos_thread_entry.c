#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* at_exit; int /*<<< orphan*/  arg; void* (* entry ) (int /*<<< orphan*/ ) ;scalar_t__ legacy; scalar_t__ name; scalar_t__ dummy; } ;
typedef  TYPE_2__ VCOS_THREAD_T ;
struct TYPE_4__ {int /*<<< orphan*/  cxt; int /*<<< orphan*/  (* pfn ) (int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  (* LEGACY_ENTRY_FN_T ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;

/* Variables and functions */
 int /*<<< orphan*/  PR_SET_NAME ; 
 int /*<<< orphan*/  _vcos_thread_current_key ; 
 int /*<<< orphan*/  prctl (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_setspecific (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *vcos_thread_entry(void *arg)
{
   int i;
   void *ret;
   VCOS_THREAD_T *thread = (VCOS_THREAD_T *)arg;

   vcos_assert(thread != NULL);
   thread->dummy = 0;

   pthread_setspecific(_vcos_thread_current_key, thread);
#if defined( HAVE_PRCTL ) && defined( PR_SET_NAME )
   /* cygwin doesn't have PR_SET_NAME */
   prctl( PR_SET_NAME, (unsigned long)thread->name, 0, 0, 0 );
#endif
   if (thread->legacy)
   {
      LEGACY_ENTRY_FN_T fn = (LEGACY_ENTRY_FN_T)thread->entry;
      (*fn)(0, thread->arg);
      ret = 0;
   }
   else
   {
      ret = (*thread->entry)(thread->arg);
   }

   /* call termination functions */
   for (i=0; thread->at_exit[i].pfn != NULL; i++)
   {
      thread->at_exit[i].pfn(thread->at_exit[i].cxt);
   }

   return ret;
}