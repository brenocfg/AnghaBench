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
typedef  size_t ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  buffer; int /*<<< orphan*/  cond; scalar_t__ nonblocking; } ;
typedef  TYPE_1__ ps3_audio_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_NO_TIMEOUT ; 
 int /*<<< orphan*/  fifo_write (int /*<<< orphan*/ ,void const*,size_t) ; 
 size_t fifo_write_avail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sys_lwcond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sys_lwmutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sys_lwmutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t ps3_audio_write(void *data, const void *buf, size_t size)
{
   ps3_audio_t *aud = data;

   if (aud->nonblocking)
   {
      if (fifo_write_avail(aud->buffer) < size)
         return 0;
   }

   while (fifo_write_avail(aud->buffer) < size)
      sys_lwcond_wait(&aud->cond, 0);

   sys_lwmutex_lock(&aud->lock, SYS_NO_TIMEOUT);
   fifo_write(aud->buffer, buf, size);
   sys_lwmutex_unlock(&aud->lock);

   return size;
}