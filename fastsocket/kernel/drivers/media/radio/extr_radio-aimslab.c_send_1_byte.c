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
struct rtrack {scalar_t__ curvol; int /*<<< orphan*/  io; scalar_t__ muted; } ;

/* Variables and functions */
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep_delay (int) ; 

__attribute__((used)) static void send_1_byte(struct rtrack *rt)
{
	if (rt->curvol == 0 || rt->muted) {
		outb_p(128+64+16+4  +1, rt->io);   /* wr-enable+data high */
		outb_p(128+64+16+4+2+1, rt->io);   /* clock */
	}
	else {
		outb_p(128+64+16+8+4  +1, rt->io); /* on+wr-enable+data high */
		outb_p(128+64+16+8+4+2+1, rt->io); /* clock */
	}

	sleep_delay(1000);
}