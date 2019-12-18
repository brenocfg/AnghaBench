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
struct TYPE_4__ {scalar_t__ buf_end; scalar_t__ buf_ptr; } ;
typedef  TYPE_1__ AVIOContext ;

/* Variables and functions */
 int FFMIN (scalar_t__,int) ; 
 int /*<<< orphan*/  flush_buffer (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (scalar_t__,int,int) ; 

void ffio_fill(AVIOContext *s, int b, int count)
{
    while (count > 0) {
        int len = FFMIN(s->buf_end - s->buf_ptr, count);
        memset(s->buf_ptr, b, len);
        s->buf_ptr += len;

        if (s->buf_ptr >= s->buf_end)
            flush_buffer(s);

        count -= len;
    }
}