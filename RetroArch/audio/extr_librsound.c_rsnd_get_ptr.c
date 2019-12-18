#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_5__ {TYPE_1__ thread; int /*<<< orphan*/  fifo_buffer; } ;
typedef  TYPE_2__ rsound_t ;

/* Variables and functions */
 int fifo_read_avail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t rsnd_get_ptr(rsound_t *rd)
{
   int ptr;
   slock_lock(rd->thread.mutex);
   ptr = fifo_read_avail(rd->fifo_buffer);
   slock_unlock(rd->thread.mutex);

   return ptr;
}