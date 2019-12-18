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
struct stliport {scalar_t__ rc; int /*<<< orphan*/  state; int /*<<< orphan*/  raw_wait; } ;
struct stlibrd {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  ST_CMDING ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stli_sendcmd (struct stlibrd*,struct stliport*,unsigned long,void*,int,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int stli_cmdwait(struct stlibrd *brdp, struct stliport *portp, unsigned long cmd, void *arg, int size, int copyback)
{
	wait_event_interruptible(portp->raw_wait,
			!test_bit(ST_CMDING, &portp->state));
	if (signal_pending(current))
		return -ERESTARTSYS;

	stli_sendcmd(brdp, portp, cmd, arg, size, copyback);

	wait_event_interruptible(portp->raw_wait,
			!test_bit(ST_CMDING, &portp->state));
	if (signal_pending(current))
		return -ERESTARTSYS;

	if (portp->rc != 0)
		return -EIO;
	return 0;
}