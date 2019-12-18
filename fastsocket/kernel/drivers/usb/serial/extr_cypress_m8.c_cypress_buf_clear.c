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
struct cypress_buf {int /*<<< orphan*/  buf_put; int /*<<< orphan*/  buf_get; } ;

/* Variables and functions */

__attribute__((used)) static void cypress_buf_clear(struct cypress_buf *cb)
{
	if (cb != NULL)
		cb->buf_get = cb->buf_put;
		/* equivalent to a get of all data available */
}