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
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  buffer; } ;
typedef  TYPE_1__ coreaudio_t ;

/* Variables and functions */
 size_t fifo_write_avail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t coreaudio_write_avail(void *data)
{
   size_t avail;
   coreaudio_t *dev = (coreaudio_t*)data;

   slock_lock(dev->lock);
   avail = fifo_write_avail(dev->buffer);
   slock_unlock(dev->lock);

   return avail;
}