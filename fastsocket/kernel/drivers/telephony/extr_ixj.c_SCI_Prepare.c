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
typedef  int /*<<< orphan*/  IXJ ;

/* Variables and functions */
 int /*<<< orphan*/  SCI_Control (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCI_End ; 
 int /*<<< orphan*/  SCI_WaitLowSCI (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int SCI_Prepare(IXJ *j)
{
	if (!SCI_Control(j, SCI_End))
		return 0;

	if (!SCI_WaitLowSCI(j))
		return 0;

	return 1;
}