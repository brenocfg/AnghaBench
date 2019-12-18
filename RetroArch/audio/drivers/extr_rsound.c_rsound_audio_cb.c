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
struct TYPE_2__ {int /*<<< orphan*/  cond; int /*<<< orphan*/  buffer; } ;
typedef  TYPE_1__ rsd_t ;

/* Variables and functions */
 int /*<<< orphan*/  fifo_read (int /*<<< orphan*/ ,void*,size_t) ; 
 size_t fifo_read_avail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scond_signal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t rsound_audio_cb(void *data, size_t bytes, void *userdata)
{
   rsd_t *rsd = (rsd_t*)userdata;

   size_t avail = fifo_read_avail(rsd->buffer);
   size_t write_size = bytes > avail ? avail : bytes;
   fifo_read(rsd->buffer, data, write_size);
   scond_signal(rsd->cond);

   return write_size;
}