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
 int /*<<< orphan*/  PPC_LDD7 ; 
 int /*<<< orphan*/  PPDR ; 
 int /*<<< orphan*/  PPSR ; 

__attribute__((used)) static void jornada720_set_vpp(int vpp)
{
	if (vpp)
		/* enabling flash write (line 470 of HP's doc) */
		PPSR |= PPC_LDD7;
	else
		/* disabling flash write (line 470 of HP's doc) */
		PPSR &= ~PPC_LDD7;
	PPDR |= PPC_LDD7;
}