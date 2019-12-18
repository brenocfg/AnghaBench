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
typedef  int u16 ;

/* Variables and functions */
 scalar_t__* adbhid ; 
 int /*<<< orphan*/  adbhid_input_unregister (int) ; 

__attribute__((used)) static void
adbhid_input_devcleanup(u16 exist)
{
	int i;
	for(i=1; i<16; i++)
		if (adbhid[i] && !(exist&(1<<i)))
			adbhid_input_unregister(i);
}