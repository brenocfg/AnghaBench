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
struct TYPE_2__ {int /*<<< orphan*/ * next; } ;
struct buffer {int /*<<< orphan*/ * current; int /*<<< orphan*/ * last; TYPE_1__ first; } ;

/* Variables and functions */

__attribute__((used)) static void
buffer_init(struct buffer *buffer)
   /* Call this only once for a given buffer */
{
   buffer->first.next = NULL;
   buffer->last = NULL;
   buffer->current = NULL;
}