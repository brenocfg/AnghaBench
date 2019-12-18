#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  sema; int /*<<< orphan*/  process_lock; int /*<<< orphan*/  lock; scalar_t__ mmal; } ;
typedef  TYPE_1__ BRCMJPEG_T ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  mmal_wrapper_destroy (scalar_t__) ; 
 int /*<<< orphan*/  vcos_mutex_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_semaphore_delete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void brcmjpeg_destroy(BRCMJPEG_T *ctx)
{
   if (ctx->mmal)
      mmal_wrapper_destroy(ctx->mmal);
   vcos_mutex_delete(&ctx->lock);
   vcos_mutex_delete(&ctx->process_lock);
   vcos_semaphore_delete(&ctx->sema);
   free(ctx);
}