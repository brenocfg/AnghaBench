#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
struct TYPE_4__ {int alive; int /*<<< orphan*/  lock; int /*<<< orphan*/  cond; int /*<<< orphan*/  driver_data; TYPE_1__* driver; } ;
typedef  TYPE_2__ audio_thread_t ;
struct TYPE_3__ {scalar_t__ (* write ) (int /*<<< orphan*/ ,void const*,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  scond_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,void const*,size_t) ; 

__attribute__((used)) static ssize_t audio_thread_write(void *data, const void *buf, size_t size)
{
   ssize_t ret;
   audio_thread_t *thr = (audio_thread_t*)data;

   if (!thr)
      return 0;

   ret = thr->driver->write(thr->driver_data, buf, size);

   if (ret < 0)
   {
      slock_lock(thr->lock);
      thr->alive = false;
      scond_signal(thr->cond);
      slock_unlock(thr->lock);
   }

   return ret;
}