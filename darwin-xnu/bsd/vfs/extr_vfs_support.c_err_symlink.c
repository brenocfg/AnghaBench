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
struct vnop_symlink_args {int dummy; } ;

/* Variables and functions */
 int ENOTSUP ; 
 int /*<<< orphan*/  nop_symlink (struct vnop_symlink_args*) ; 

int
err_symlink(struct vnop_symlink_args *ap)
{
	(void)nop_symlink(ap);
	return (ENOTSUP);
}