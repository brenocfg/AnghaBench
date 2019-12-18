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
struct TYPE_3__ {int preview_stop; int /*<<< orphan*/  preview_thread; } ;
typedef  TYPE_1__ RASPITEX_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  vcos_log_trace (char*) ; 
 int /*<<< orphan*/  vcos_thread_join (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void raspitex_stop(RASPITEX_STATE *state)
{
   if (! state->preview_stop)
   {
      vcos_log_trace("Stopping GL preview");
      state->preview_stop = 1;
      vcos_thread_join(&state->preview_thread, NULL);
   }
}