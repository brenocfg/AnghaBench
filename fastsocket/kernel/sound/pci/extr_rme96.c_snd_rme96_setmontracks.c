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
struct rme96 {scalar_t__ iobase; int /*<<< orphan*/  wcreg; } ;

/* Variables and functions */
 scalar_t__ RME96_IO_CONTROL_REGISTER ; 
 int /*<<< orphan*/  RME96_WCR_MONITOR_0 ; 
 int /*<<< orphan*/  RME96_WCR_MONITOR_1 ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
snd_rme96_setmontracks(struct rme96 *rme96,
		       int montracks)
{
	if (montracks & 1) {
		rme96->wcreg |= RME96_WCR_MONITOR_0;
	} else {
		rme96->wcreg &= ~RME96_WCR_MONITOR_0;
	}
	if (montracks & 2) {
		rme96->wcreg |= RME96_WCR_MONITOR_1;
	} else {
		rme96->wcreg &= ~RME96_WCR_MONITOR_1;
	}
	writel(rme96->wcreg, rme96->iobase + RME96_IO_CONTROL_REGISTER);
	return 0;
}