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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {unsigned int writing; scalar_t__ max_ptr; scalar_t__ ptr; int /*<<< orphan*/  size; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ memstream_t ;

/* Variables and functions */

__attribute__((used)) static void memstream_init(memstream_t *stream,
      uint8_t *buffer, uint64_t max_size, unsigned writing)
{
   if (!stream)
      return;

   stream->buf     = buffer;
   stream->size    = max_size;
   stream->ptr     = 0;
   stream->max_ptr = 0;
   stream->writing = writing;
}