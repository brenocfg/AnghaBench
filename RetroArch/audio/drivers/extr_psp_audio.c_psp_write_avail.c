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
typedef  size_t uint16_t ;
struct TYPE_2__ {int /*<<< orphan*/  fifo_lock; scalar_t__ read_pos; scalar_t__ write_pos; int /*<<< orphan*/  running; } ;
typedef  TYPE_1__ psp_audio_t ;

/* Variables and functions */
 size_t AUDIO_BUFFER_SIZE ; 
 size_t AUDIO_BUFFER_SIZE_MASK ; 
 int /*<<< orphan*/  slock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t psp_write_avail(void *data)
{
   size_t val;
   psp_audio_t* psp = (psp_audio_t*)data;

   if (!psp||!psp->running)
      return 0;
   slock_lock(psp->fifo_lock);
   val = AUDIO_BUFFER_SIZE - ((uint16_t)
         (psp->write_pos - psp->read_pos) & AUDIO_BUFFER_SIZE_MASK);
   slock_unlock(psp->fifo_lock);
   return val;
}