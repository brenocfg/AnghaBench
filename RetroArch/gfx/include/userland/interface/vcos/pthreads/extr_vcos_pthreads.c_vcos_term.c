#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  suspend; } ;

/* Variables and functions */
 int VCOS_INIT_MAIN_SEM ; 
 int VCOS_INIT_MSGQ ; 
 int VCOS_INIT_NAMED_SEM ; 
 int VCOS_INIT_PRINTF_LOCK ; 
 int /*<<< orphan*/  _vcos_named_semaphore_deinit () ; 
 int /*<<< orphan*/  printf_lock ; 
 int /*<<< orphan*/  vcos_msgq_deinit () ; 
 int /*<<< orphan*/  vcos_mutex_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_semaphore_delete (int /*<<< orphan*/ *) ; 
 TYPE_1__ vcos_thread_main ; 

__attribute__((used)) static void vcos_term(uint32_t flags)
{
   if (flags & VCOS_INIT_MSGQ)
      vcos_msgq_deinit();

   if (flags & VCOS_INIT_MAIN_SEM)
      vcos_semaphore_delete(&vcos_thread_main.suspend);

#ifdef ANDROID
   if (flags & VCOS_INIT_PRINTF_LOCK)
      vcos_mutex_delete(&printf_lock);
#endif

   if (flags & VCOS_INIT_NAMED_SEM)
      _vcos_named_semaphore_deinit();
}