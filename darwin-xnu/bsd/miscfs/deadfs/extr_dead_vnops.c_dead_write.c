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
struct vnop_write_args {int /*<<< orphan*/  a_vp; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ chkvnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 

int
dead_write(struct vnop_write_args *ap)
{

	if (chkvnlock(ap->a_vp))
		panic("dead_write: lock");
	return (EIO);
}