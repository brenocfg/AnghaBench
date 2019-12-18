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
struct trust {int curstereo; int ioval; int /*<<< orphan*/  lock; int /*<<< orphan*/  io; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tr_setstereo(struct trust *tr, int stereo)
{
	mutex_lock(&tr->lock);
	tr->curstereo = !!stereo;
	tr->ioval = (tr->ioval & 0xfb) | (!tr->curstereo << 2);
	outb(tr->ioval, tr->io);
	mutex_unlock(&tr->lock);
}