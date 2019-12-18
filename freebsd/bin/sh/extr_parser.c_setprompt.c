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

/* Variables and functions */
 int /*<<< orphan*/  el ; 
 int /*<<< orphan*/  flushout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getprompt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  out2 ; 
 int /*<<< orphan*/  out2str (int /*<<< orphan*/ ) ; 
 int whichprompt ; 

__attribute__((used)) static void
setprompt(int which)
{
	whichprompt = which;
	if (which == 0)
		return;

#ifndef NO_HISTORY
	if (!el)
#endif
	{
		out2str(getprompt(NULL));
		flushout(out2);
	}
}