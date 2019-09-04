#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xsockbuf {short sb_timeo; int /*<<< orphan*/  sb_flags; int /*<<< orphan*/  sb_lowat; int /*<<< orphan*/  sb_mbmax; int /*<<< orphan*/  sb_mbcnt; int /*<<< orphan*/  sb_hiwat; int /*<<< orphan*/  sb_cc; } ;
struct TYPE_2__ {int tv_sec; short tv_usec; } ;
struct sockbuf {TYPE_1__ sb_timeo; int /*<<< orphan*/  sb_flags; int /*<<< orphan*/  sb_lowat; int /*<<< orphan*/  sb_mbmax; int /*<<< orphan*/  sb_mbcnt; int /*<<< orphan*/  sb_hiwat; int /*<<< orphan*/  sb_cc; } ;

/* Variables and functions */
 int hz ; 
 short tick ; 

void
sbtoxsockbuf(struct sockbuf *sb, struct xsockbuf *xsb)
{
	xsb->sb_cc = sb->sb_cc;
	xsb->sb_hiwat = sb->sb_hiwat;
	xsb->sb_mbcnt = sb->sb_mbcnt;
	xsb->sb_mbmax = sb->sb_mbmax;
	xsb->sb_lowat = sb->sb_lowat;
	xsb->sb_flags = sb->sb_flags;
	xsb->sb_timeo = (short)
	    (sb->sb_timeo.tv_sec * hz) + sb->sb_timeo.tv_usec / tick;
	if (xsb->sb_timeo == 0 && sb->sb_timeo.tv_usec != 0)
		xsb->sb_timeo = 1;
}