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
struct msgbuf {char* msg_bufc; scalar_t__ msg_bufx; scalar_t__ msg_size; } ;

/* Variables and functions */

void
log_putc_locked(struct msgbuf *mbp, char c)
{
	mbp->msg_bufc[mbp->msg_bufx++] = c;
	if (mbp->msg_bufx >= mbp->msg_size)
		mbp->msg_bufx = 0;
}