#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct buffer {int /*<<< orphan*/ * current; scalar_t__ end_count; int /*<<< orphan*/  first; int /*<<< orphan*/ * last; } ;

/* Variables and functions */

__attribute__((used)) static void
buffer_start_write(struct buffer *buffer)
{
   buffer->last = &buffer->first;
   buffer->end_count = 0;
   buffer->current = NULL;
}