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
struct buffer_head {void* b_private; int /*<<< orphan*/ * b_end_io; } ;
typedef  int /*<<< orphan*/  bh_end_io_t ;

/* Variables and functions */

inline void
init_buffer(struct buffer_head *bh, bh_end_io_t *handler, void *private)
{
	bh->b_end_io = handler;
	bh->b_private = private;
}