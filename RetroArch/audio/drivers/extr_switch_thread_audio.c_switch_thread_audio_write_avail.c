#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  fifoLock; int /*<<< orphan*/  fifo; } ;
typedef  TYPE_1__ switch_thread_audio_t ;

/* Variables and functions */
 int /*<<< orphan*/  compat_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compat_mutex_unlock (int /*<<< orphan*/ *) ; 
 size_t fifo_write_avail (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t switch_thread_audio_write_avail(void *data)
{
   size_t val;
   switch_thread_audio_t* swa = (switch_thread_audio_t*)data;

   compat_mutex_lock(&swa->fifoLock);
   val = fifo_write_avail(swa->fifo);
   compat_mutex_unlock(&swa->fifoLock);

   return val;
}