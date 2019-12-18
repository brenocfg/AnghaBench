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
struct TYPE_2__ {int /*<<< orphan*/  rd; int /*<<< orphan*/  buffer; scalar_t__ has_error; } ;
typedef  TYPE_1__ rsd_t ;

/* Variables and functions */
 size_t fifo_write_avail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsd_callback_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsd_callback_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t rs_write_avail(void *data)
{
   size_t val;
   rsd_t *rsd = (rsd_t*)data;

   if (rsd->has_error)
      return 0;
   rsd_callback_lock(rsd->rd);
   val = fifo_write_avail(rsd->buffer);
   rsd_callback_unlock(rsd->rd);
   return val;
}