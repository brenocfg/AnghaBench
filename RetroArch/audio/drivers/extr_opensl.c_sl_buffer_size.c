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
struct TYPE_2__ {size_t buf_size; size_t buf_count; } ;
typedef  TYPE_1__ sl_t ;

/* Variables and functions */

__attribute__((used)) static size_t sl_buffer_size(void *data)
{
   sl_t *sl = (sl_t*)data;
   return sl->buf_size * sl->buf_count;
}