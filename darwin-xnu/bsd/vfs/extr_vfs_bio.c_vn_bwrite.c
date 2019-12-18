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
struct vnop_bwrite_args {int /*<<< orphan*/  a_bp; } ;

/* Variables and functions */
 int buf_bwrite (int /*<<< orphan*/ ) ; 

int
vn_bwrite(struct vnop_bwrite_args *ap)
{
	return (buf_bwrite(ap->a_bp));
}