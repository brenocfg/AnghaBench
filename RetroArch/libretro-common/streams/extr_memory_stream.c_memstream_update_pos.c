#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ ptr; scalar_t__ max_ptr; } ;
typedef  TYPE_1__ memstream_t ;

/* Variables and functions */

__attribute__((used)) static void memstream_update_pos(memstream_t *stream)
{
   if (stream && stream->ptr > stream->max_ptr)
      stream->max_ptr = stream->ptr;
}