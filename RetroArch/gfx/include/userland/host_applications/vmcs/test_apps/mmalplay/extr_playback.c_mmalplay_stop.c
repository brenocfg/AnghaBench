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
struct TYPE_3__ {int stop; int /*<<< orphan*/  event; } ;
typedef  TYPE_1__ MMALPLAY_T ;

/* Variables and functions */
 int /*<<< orphan*/  vcos_semaphore_post (int /*<<< orphan*/ *) ; 

void mmalplay_stop(MMALPLAY_T *ctx)
{
   ctx->stop = 1;
   vcos_semaphore_post(&ctx->event);
}