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
struct TYPE_3__ {int is_paused; } ;
typedef  TYPE_1__ audio_thread_t ;

/* Variables and functions */
 int /*<<< orphan*/  audio_driver_disable_callback () ; 
 int /*<<< orphan*/  audio_thread_block (TYPE_1__*) ; 

__attribute__((used)) static bool audio_thread_stop(void *data)
{
   audio_thread_t *thr = (audio_thread_t*)data;

   if (!thr)
      return false;

   audio_thread_block(thr);
   thr->is_paused = true;

   audio_driver_disable_callback();

   return true;
}