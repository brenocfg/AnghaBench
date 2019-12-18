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
struct vnop_strategy_args {int /*<<< orphan*/  a_bp; } ;

/* Variables and functions */
 int EIO ; 
 int VNOP_STRATEGY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buf_biodone (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buf_seterror (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * buf_vnode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chkvnlock (int /*<<< orphan*/ *) ; 

int
dead_strategy(struct vnop_strategy_args *ap)
{

	if (buf_vnode(ap->a_bp) == NULL || !chkvnlock(buf_vnode(ap->a_bp))) {
	        buf_seterror(ap->a_bp, EIO);
		buf_biodone(ap->a_bp);
		return (EIO);
	}
	return (VNOP_STRATEGY(ap->a_bp));
}