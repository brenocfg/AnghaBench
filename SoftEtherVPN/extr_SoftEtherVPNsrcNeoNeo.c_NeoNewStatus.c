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
typedef  int /*<<< orphan*/  NEO_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  NeoZero (int /*<<< orphan*/ *,int) ; 

void NeoNewStatus(NEO_STATUS *s)
{
	// Validate arguments
	if (s == NULL)
	{
		return;
	}

	// Memory initialization
	NeoZero(s, sizeof(NEO_STATUS));
}