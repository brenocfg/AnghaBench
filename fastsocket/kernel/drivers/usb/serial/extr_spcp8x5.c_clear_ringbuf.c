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
struct ringbuf {int /*<<< orphan*/  buf_put; int /*<<< orphan*/  buf_get; } ;

/* Variables and functions */

__attribute__((used)) static inline void clear_ringbuf(struct ringbuf *pb)
{
	if (pb != NULL)
		pb->buf_get = pb->buf_put;
}