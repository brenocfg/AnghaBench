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
struct sockbuf {scalar_t__ sb_waiters; int /*<<< orphan*/  sb_cc; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ ) ; 

void
sbwakeup(struct sockbuf *sb)
{
	if (sb->sb_waiters > 0)
		wakeup((caddr_t)&sb->sb_cc);
}