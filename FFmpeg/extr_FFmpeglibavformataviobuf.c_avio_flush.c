#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ buf_ptr_max; scalar_t__ buf_ptr; scalar_t__ write_flag; } ;
typedef  TYPE_1__ AVIOContext ;

/* Variables and functions */
 int FFMIN (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  avio_seek (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_buffer (TYPE_1__*) ; 

void avio_flush(AVIOContext *s)
{
    int seekback = s->write_flag ? FFMIN(0, s->buf_ptr - s->buf_ptr_max) : 0;
    flush_buffer(s);
    if (seekback)
        avio_seek(s, seekback, SEEK_CUR);
}