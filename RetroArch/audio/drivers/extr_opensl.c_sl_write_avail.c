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
struct TYPE_2__ {int buf_count; int buf_size; scalar_t__ buffer_ptr; scalar_t__ buffered_blocks; } ;
typedef  TYPE_1__ sl_t ;

/* Variables and functions */

__attribute__((used)) static size_t sl_write_avail(void *data)
{
   sl_t *sl = (sl_t*)data;
   size_t avail = (sl->buf_count - (int)sl->buffered_blocks - 1) * sl->buf_size + (sl->buf_size - (int)sl->buffer_ptr);
   return avail;
}