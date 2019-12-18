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
struct vnop_fsync_args {int /*<<< orphan*/  a_context; int /*<<< orphan*/  a_waitfor; int /*<<< orphan*/  a_vp; } ;

/* Variables and functions */
 int spec_fsync_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
spec_fsync(struct vnop_fsync_args *ap)
{
	return spec_fsync_internal(ap->a_vp, ap->a_waitfor, ap->a_context);
}