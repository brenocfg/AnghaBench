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
struct TYPE_2__ {int /*<<< orphan*/  ch_count; } ;
struct SwrContext {TYPE_1__ in_buffer; } ;

/* Variables and functions */

int swr_is_initialized(struct SwrContext *s) {
    return !!s->in_buffer.ch_count;
}