#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ref_count; } ;
typedef  TYPE_1__ BRCMJPEG_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK_COMP (TYPE_1__*) ; 
 int /*<<< orphan*/  UNLOCK_COMP (TYPE_1__*) ; 

void brcmjpeg_acquire(BRCMJPEG_T *ctx)
{
   LOCK_COMP(ctx);
   ctx->ref_count++;
   UNLOCK_COMP(ctx);
}