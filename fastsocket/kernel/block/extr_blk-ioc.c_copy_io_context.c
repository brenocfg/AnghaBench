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
struct io_context {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  atomic_long_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_long_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_io_context (struct io_context*) ; 

void copy_io_context(struct io_context **pdst, struct io_context **psrc)
{
	struct io_context *src = *psrc;
	struct io_context *dst = *pdst;

	if (src) {
		BUG_ON(atomic_long_read(&src->refcount) == 0);
		atomic_long_inc(&src->refcount);
		put_io_context(dst);
		*pdst = src;
	}
}