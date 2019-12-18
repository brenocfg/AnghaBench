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
typedef  int /*<<< orphan*/  u_char ;
struct IsdnCardState {char* dlog; } ;

/* Variables and functions */
 int /*<<< orphan*/  HiSax_putstatus (struct IsdnCardState*,char*,char*,...) ; 
 int MAX_DLOG_SPACE ; 
 int /*<<< orphan*/  QuickHex (char*,int /*<<< orphan*/ *,int) ; 

void
LogFrame(struct IsdnCardState *cs, u_char * buf, int size)
{
	char *dp;

	if (size < 1)
		return;
	dp = cs->dlog;
	if (size < MAX_DLOG_SPACE / 3 - 10) {
		*dp++ = 'H';
		*dp++ = 'E';
		*dp++ = 'X';
		*dp++ = ':';
		dp += QuickHex(dp, buf, size);
		dp--;
		*dp++ = '\n';
		*dp = 0;
		HiSax_putstatus(cs, NULL, cs->dlog);
	} else
		HiSax_putstatus(cs, "LogFrame: ", "warning Frame too big (%d)", size);
}