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
struct TYPE_3__ {int /*<<< orphan*/  in_buffer; int /*<<< orphan*/  read_in_ptr; scalar_t__ remaining_in_len; } ;
typedef  TYPE_1__ MMSContext ;

/* Variables and functions */

__attribute__((used)) static void clear_stream_buffers(MMSContext *mms)
{
    mms->remaining_in_len = 0;
    mms->read_in_ptr      = mms->in_buffer;
}