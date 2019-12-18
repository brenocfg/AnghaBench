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
struct TYPE_2__ {int /*<<< orphan*/  fifo_lock; int /*<<< orphan*/  buffer; scalar_t__ thread_dead; } ;
typedef  TYPE_1__ alsa_thread_t ;

/* Variables and functions */
 size_t fifo_write_avail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t alsa_thread_write_avail(void *data)
{
   alsa_thread_t *alsa = (alsa_thread_t*)data;
   size_t val;

   if (alsa->thread_dead)
      return 0;
   slock_lock(alsa->fifo_lock);
   val = fifo_write_avail(alsa->buffer);
   slock_unlock(alsa->fifo_lock);
   return val;
}