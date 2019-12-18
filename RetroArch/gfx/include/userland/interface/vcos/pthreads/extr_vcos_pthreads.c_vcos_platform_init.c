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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ VCOS_STATUS_T ;
struct TYPE_3__ {int /*<<< orphan*/  thread; int /*<<< orphan*/  suspend; } ;

/* Variables and functions */
 scalar_t__ VCOS_EINVAL ; 
 int /*<<< orphan*/  VCOS_INIT_MAIN_SEM ; 
 int /*<<< orphan*/  VCOS_INIT_MSGQ ; 
 int /*<<< orphan*/  VCOS_INIT_NAMED_SEM ; 
 int /*<<< orphan*/  VCOS_INIT_PRINTF_LOCK ; 
 scalar_t__ VCOS_SUCCESS ; 
 scalar_t__ _vcos_named_semaphore_init () ; 
 int /*<<< orphan*/  _vcos_thread_current_key ; 
 int /*<<< orphan*/  current_thread_key_init ; 
 int /*<<< orphan*/  current_thread_key_once ; 
 int /*<<< orphan*/  mtrace () ; 
 int /*<<< orphan*/  printf_lock ; 
 int /*<<< orphan*/  pthread_self () ; 
 int pthread_setspecific (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  vcos_logging_init () ; 
 scalar_t__ vcos_msgq_init () ; 
 scalar_t__ vcos_mutex_create (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ vcos_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ vcos_semaphore_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_term (int /*<<< orphan*/ ) ; 
 TYPE_1__ vcos_thread_main ; 
 int /*<<< orphan*/  vcos_verify (int) ; 

VCOS_STATUS_T vcos_platform_init(void)
{
   VCOS_STATUS_T st;
   uint32_t flags = 0;
   int pst;

   st = _vcos_named_semaphore_init();
   if (!vcos_verify(st == VCOS_SUCCESS))
      goto end;

   flags |= VCOS_INIT_NAMED_SEM;

#ifdef HAVE_MTRACE
   /* enable glibc memory debugging, if the environment
    * variable MALLOC_TRACE names a valid file.
    */
   mtrace();
#endif

#ifdef ANDROID
   st = vcos_mutex_create(&printf_lock, "printf");
   if (!vcos_verify(st == VCOS_SUCCESS))
      goto end;

   flags |= VCOS_INIT_PRINTF_LOCK;
#endif

   st = vcos_once(&current_thread_key_once, current_thread_key_init);
   if (!vcos_verify(st == VCOS_SUCCESS))
      goto end;

   /* Initialise a VCOS wrapper for the thread which called vcos_init. */
   st = vcos_semaphore_create(&vcos_thread_main.suspend, NULL, 0);
   if (!vcos_verify(st == VCOS_SUCCESS))
      goto end;

   flags |= VCOS_INIT_MAIN_SEM;

   vcos_thread_main.thread = pthread_self();

   pst = pthread_setspecific(_vcos_thread_current_key, &vcos_thread_main);
   if (!vcos_verify(pst == 0))
   {
      st = VCOS_EINVAL;
      goto end;
   }

   st = vcos_msgq_init();
   if (!vcos_verify(st == VCOS_SUCCESS))
      goto end;

   flags |= VCOS_INIT_MSGQ;

   vcos_logging_init();

end:
   if (st != VCOS_SUCCESS)
      vcos_term(flags);

   return st;
}