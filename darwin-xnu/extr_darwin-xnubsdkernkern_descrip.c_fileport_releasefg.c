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
struct fileglob {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROC_NULL ; 
 int /*<<< orphan*/  closef_locked (int /*<<< orphan*/ *,struct fileglob*,int /*<<< orphan*/ ) ; 

void
fileport_releasefg(struct fileglob *fg)
{
	(void)closef_locked(NULL, fg, PROC_NULL);

	return;
}