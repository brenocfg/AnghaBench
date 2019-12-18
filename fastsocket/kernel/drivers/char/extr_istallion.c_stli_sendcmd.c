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
struct stliport {int dummy; } ;
struct stlibrd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __stli_sendcmd (struct stlibrd*,struct stliport*,unsigned long,void*,int,int) ; 
 int /*<<< orphan*/  brd_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void stli_sendcmd(struct stlibrd *brdp, struct stliport *portp, unsigned long cmd, void *arg, int size, int copyback)
{
	unsigned long		flags;

	spin_lock_irqsave(&brd_lock, flags);
	__stli_sendcmd(brdp, portp, cmd, arg, size, copyback);
	spin_unlock_irqrestore(&brd_lock, flags);
}