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
struct vnop_lookup_args {int /*<<< orphan*/ ** a_vpp; } ;

/* Variables and functions */
 int ENOTDIR ; 

int
dead_lookup(struct vnop_lookup_args *ap)
{

	*ap->a_vpp = NULL;
	return (ENOTDIR);
}