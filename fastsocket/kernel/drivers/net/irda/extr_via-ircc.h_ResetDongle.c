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
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  ActClk (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ClkTx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Tdelay (int) ; 

__attribute__((used)) static void ResetDongle(__u16 iobase)
{
	int i;
	ClkTx(iobase, 0, 0);
	Tdelay(1);
	for (i = 0; i < 30; i++) {
		ActClk(iobase, 1);
		Tdelay(1);
		ActClk(iobase, 0);
		Tdelay(1);
	}
	ActClk(iobase, 0);
}