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
struct buffer {scalar_t__ read_count; int /*<<< orphan*/  first; int /*<<< orphan*/ * current; } ;

/* Variables and functions */

__attribute__((used)) static void
buffer_start_read(struct buffer *buffer)
{
   buffer->current = &buffer->first;
   buffer->read_count = 0;
}