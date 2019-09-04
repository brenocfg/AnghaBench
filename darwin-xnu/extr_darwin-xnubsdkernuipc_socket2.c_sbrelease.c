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
struct sockbuf {scalar_t__ sb_mbmax; scalar_t__ sb_hiwat; } ;

/* Variables and functions */
 int /*<<< orphan*/  sbflush (struct sockbuf*) ; 

void
sbrelease(struct sockbuf *sb)
{
	sbflush(sb);
	sb->sb_hiwat = 0;
	sb->sb_mbmax = 0;
}