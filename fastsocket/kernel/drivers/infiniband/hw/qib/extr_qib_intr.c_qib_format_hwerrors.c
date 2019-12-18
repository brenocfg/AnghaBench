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
typedef  int u64 ;
struct qib_hwerror_msgs {int mask; int /*<<< orphan*/  msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  qib_format_hwmsg (char*,size_t,int /*<<< orphan*/ ) ; 

void qib_format_hwerrors(u64 hwerrs, const struct qib_hwerror_msgs *hwerrmsgs,
			 size_t nhwerrmsgs, char *msg, size_t msgl)
{
	int i;

	for (i = 0; i < nhwerrmsgs; i++)
		if (hwerrs & hwerrmsgs[i].mask)
			qib_format_hwmsg(msg, msgl, hwerrmsgs[i].msg);
}