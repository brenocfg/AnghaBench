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
struct TYPE_3__ {int running; } ;
typedef  TYPE_1__ ps2_audio_t ;

/* Variables and functions */
 int /*<<< orphan*/  audsrv_stop_audio () ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void ps2_audio_free(void *data)
{
   ps2_audio_t* ps2 = (ps2_audio_t*)data;
   if (!ps2)
      return;

   ps2->running = false;
   audsrv_stop_audio();
   free(ps2);
}