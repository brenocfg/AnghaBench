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
struct TYPE_6__ {scalar_t__ type; scalar_t__ ref_count; } ;
typedef  TYPE_1__ BRCMJPEG_T ;

/* Variables and functions */
 scalar_t__ BRCMJPEG_TYPE_ENCODER ; 
 int /*<<< orphan*/  LOCK () ; 
 int /*<<< orphan*/  LOCK_COMP (TYPE_1__*) ; 
 int /*<<< orphan*/  UNLOCK () ; 
 int /*<<< orphan*/  UNLOCK_COMP (TYPE_1__*) ; 
 int /*<<< orphan*/ * brcmjpeg_decoder ; 
 int /*<<< orphan*/  brcmjpeg_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/ * brcmjpeg_encoder ; 

void brcmjpeg_release(BRCMJPEG_T *ctx)
{
   LOCK_COMP(ctx);
   if (--ctx->ref_count)
   {
      UNLOCK_COMP(ctx);
      return;
   }

   LOCK();
   if (ctx->type == BRCMJPEG_TYPE_ENCODER)
      brcmjpeg_encoder = NULL;
   else
      brcmjpeg_decoder = NULL;
   UNLOCK();
   UNLOCK_COMP(ctx);

   brcmjpeg_destroy(ctx);
   return;
}