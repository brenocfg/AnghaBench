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
struct vnop_blktooff_args {scalar_t__* a_offset; int /*<<< orphan*/  a_vp; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  chkvnlock (int /*<<< orphan*/ ) ; 

int
dead_blktooff(struct vnop_blktooff_args *ap)
{
    if (!chkvnlock(ap->a_vp))
		return (EIO);

	*ap->a_offset = (off_t)-1;	/* failure */
	return (0);
}