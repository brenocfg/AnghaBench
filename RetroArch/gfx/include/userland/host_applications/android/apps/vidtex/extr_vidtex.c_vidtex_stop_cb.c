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
struct TYPE_3__ {int /*<<< orphan*/  sem_decoded; int /*<<< orphan*/  stop_reason; } ;
typedef  TYPE_1__ VIDTEX_T ;

/* Variables and functions */
 int /*<<< orphan*/  vcos_semaphore_post (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vidtex_set_quit (TYPE_1__*,int) ; 

__attribute__((used)) static void vidtex_stop_cb(void *ctx, uint32_t stop_reason)
{
   VIDTEX_T *vt = ctx;
   vt->stop_reason = stop_reason;
   vidtex_set_quit(vt, true);
   vcos_semaphore_post(&vt->sem_decoded);
}