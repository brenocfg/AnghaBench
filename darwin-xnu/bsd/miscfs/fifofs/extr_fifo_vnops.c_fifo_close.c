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
struct vnop_close_args {int /*<<< orphan*/  a_context; int /*<<< orphan*/  a_fflag; int /*<<< orphan*/  a_vp; } ;

/* Variables and functions */
 int fifo_close_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
fifo_close(struct vnop_close_args *ap)
{
	return fifo_close_internal(ap->a_vp, ap->a_fflag, ap->a_context, 0);
}