#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ ptr; scalar_t__ size; int* buf; } ;
typedef  TYPE_1__ memstream_t ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  memstream_update_pos (TYPE_1__*) ; 

int memstream_getc(memstream_t *stream)
{
   int ret = 0;
   if (stream->ptr >= stream->size)
      return EOF;
   ret = stream->buf[stream->ptr++];

   memstream_update_pos(stream);

   return ret;
}