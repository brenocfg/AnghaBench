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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_4__ {int quit_thread; int /*<<< orphan*/  cond; int /*<<< orphan*/  cond_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/  buffer; int /*<<< orphan*/  audio_port; int /*<<< orphan*/  thread; } ;
typedef  TYPE_1__ ps3_audio_t ;

/* Variables and functions */
 int /*<<< orphan*/  cellAudioPortClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cellAudioQuit () ; 
 int /*<<< orphan*/  fifo_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  ps3_audio_start (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ps3_audio_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  sys_lwcond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sys_lwmutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sys_ppu_thread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ps3_audio_free(void *data)
{
   uint64_t val;
   ps3_audio_t *aud = data;

   aud->quit_thread = true;
   ps3_audio_start(aud, false);
   sys_ppu_thread_join(aud->thread, &val);

   ps3_audio_stop(aud);
   cellAudioPortClose(aud->audio_port);
   cellAudioQuit();
   fifo_free(aud->buffer);

   sys_lwmutex_destroy(&aud->lock);
   sys_lwmutex_destroy(&aud->cond_lock);
   sys_lwcond_destroy(&aud->cond);

   free(data);
}