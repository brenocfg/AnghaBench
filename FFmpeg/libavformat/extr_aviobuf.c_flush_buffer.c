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
struct TYPE_4__ {scalar_t__ buf_ptr_max; scalar_t__ buf_ptr; scalar_t__ buffer; scalar_t__ checksum_ptr; scalar_t__ buf_end; scalar_t__ write_flag; int /*<<< orphan*/  checksum; int /*<<< orphan*/  (* update_checksum ) (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ;} ;
typedef  TYPE_1__ AVIOContext ;

/* Variables and functions */
 scalar_t__ FFMAX (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  writeout (TYPE_1__*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void flush_buffer(AVIOContext *s)
{
    s->buf_ptr_max = FFMAX(s->buf_ptr, s->buf_ptr_max);
    if (s->write_flag && s->buf_ptr_max > s->buffer) {
        writeout(s, s->buffer, s->buf_ptr_max - s->buffer);
        if (s->update_checksum) {
            s->checksum     = s->update_checksum(s->checksum, s->checksum_ptr,
                                                 s->buf_ptr_max - s->checksum_ptr);
            s->checksum_ptr = s->buffer;
        }
    }
    s->buf_ptr = s->buf_ptr_max = s->buffer;
    if (!s->write_flag)
        s->buf_end = s->buffer;
}