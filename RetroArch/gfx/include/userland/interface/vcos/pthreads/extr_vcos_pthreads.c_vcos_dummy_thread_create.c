#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int dummy; int /*<<< orphan*/  suspend; int /*<<< orphan*/  thread; } ;
typedef  TYPE_1__ VCOS_THREAD_T ;
typedef  scalar_t__ VCOS_STATUS_T ;

/* Variables and functions */
 scalar_t__ VCOS_SUCCESS ; 
 int /*<<< orphan*/  _vcos_thread_current_key ; 
 int /*<<< orphan*/  current_thread_key_init ; 
 int /*<<< orphan*/  current_thread_key_once ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pthread_self () ; 
 int pthread_setspecific (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  vcos_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_free (TYPE_1__*) ; 
 scalar_t__ vcos_malloc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ vcos_semaphore_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

VCOS_THREAD_T *vcos_dummy_thread_create(void)
{
   VCOS_STATUS_T st;
   VCOS_THREAD_T *thread_hndl = NULL;
   int rc;

   thread_hndl = (VCOS_THREAD_T *)vcos_malloc(sizeof(VCOS_THREAD_T), NULL);
   vcos_assert(thread_hndl != NULL);

   memset(thread_hndl, 0, sizeof(VCOS_THREAD_T));

   thread_hndl->dummy = 1;
   thread_hndl->thread = pthread_self();

   st = vcos_semaphore_create(&thread_hndl->suspend, NULL, 0);
   if (st != VCOS_SUCCESS)
   {
      vcos_free(thread_hndl);
      return( thread_hndl );
   }

   vcos_once(&current_thread_key_once, current_thread_key_init);

   rc = pthread_setspecific(_vcos_thread_current_key,
                            thread_hndl);
   (void)rc;

   return( thread_hndl );
}