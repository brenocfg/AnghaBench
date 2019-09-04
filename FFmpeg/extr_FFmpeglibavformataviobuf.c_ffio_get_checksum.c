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
struct TYPE_3__ {unsigned long checksum; unsigned long (* update_checksum ) (unsigned long,scalar_t__,scalar_t__) ;scalar_t__ checksum_ptr; scalar_t__ buf_ptr; } ;
typedef  TYPE_1__ AVIOContext ;

/* Variables and functions */
 unsigned long stub1 (unsigned long,scalar_t__,scalar_t__) ; 

unsigned long ffio_get_checksum(AVIOContext *s)
{
    s->checksum = s->update_checksum(s->checksum, s->checksum_ptr,
                                     s->buf_ptr - s->checksum_ptr);
    s->update_checksum = NULL;
    return s->checksum;
}