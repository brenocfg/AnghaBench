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
struct vnop_revoke_args {int /*<<< orphan*/  a_context; int /*<<< orphan*/  a_flags; int /*<<< orphan*/  a_vp; } ;

/* Variables and functions */
 int vn_revoke (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
nop_revoke(struct vnop_revoke_args *ap)
{
	return vn_revoke(ap->a_vp, ap->a_flags, ap->a_context);
}