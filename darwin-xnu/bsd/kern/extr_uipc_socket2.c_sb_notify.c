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
struct sockbuf {scalar_t__ sb_waiters; int sb_flags; } ;

/* Variables and functions */
 int SB_ASYNC ; 
 int SB_KNOTE ; 
 int SB_SEL ; 
 int SB_UPCALL ; 

int
sb_notify(struct sockbuf *sb)
{
	return (sb->sb_waiters > 0 ||
	    (sb->sb_flags & (SB_SEL|SB_ASYNC|SB_UPCALL|SB_KNOTE)));
}