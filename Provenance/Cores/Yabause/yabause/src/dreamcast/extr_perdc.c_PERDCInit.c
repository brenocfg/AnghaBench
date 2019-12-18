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
 int /*<<< orphan*/  PORTDATA1 ; 
 int /*<<< orphan*/  PerPadAdd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PerPortReset () ; 
 int /*<<< orphan*/  pad1 ; 

int PERDCInit(void)	{
    PerPortReset();
    pad1 = PerPadAdd(&PORTDATA1);
	return 0;
}