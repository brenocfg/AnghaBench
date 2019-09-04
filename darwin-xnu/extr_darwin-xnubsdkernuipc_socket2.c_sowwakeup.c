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
struct socket {int /*<<< orphan*/  so_snd; } ;

/* Variables and functions */
 scalar_t__ sb_notify (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sowakeup (struct socket*,int /*<<< orphan*/ *) ; 

void
sowwakeup(struct socket *so)
{
	if (sb_notify(&so->so_snd))
		sowakeup(so, &so->so_snd);
}