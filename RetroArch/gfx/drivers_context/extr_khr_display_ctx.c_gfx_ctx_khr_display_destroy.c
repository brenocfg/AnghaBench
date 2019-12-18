#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ queue_lock; } ;
struct TYPE_7__ {TYPE_1__ context; } ;
struct TYPE_6__ {TYPE_3__ vk; } ;
typedef  TYPE_2__ khr_display_ctx_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  slock_free (scalar_t__) ; 
 int /*<<< orphan*/  vulkan_context_destroy (TYPE_3__*,int) ; 

__attribute__((used)) static void gfx_ctx_khr_display_destroy(void *data)
{
   khr_display_ctx_data_t *khr = (khr_display_ctx_data_t*)data;
   if (!khr)
      return;

   vulkan_context_destroy(&khr->vk, true);
#ifdef HAVE_THREADS
   if (khr->vk.context.queue_lock)
      slock_free(khr->vk.context.queue_lock);
#endif
   free(khr);
}