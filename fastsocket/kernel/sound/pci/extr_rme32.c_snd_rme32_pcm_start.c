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
struct rme32 {scalar_t__ iobase; int /*<<< orphan*/  wcreg; } ;

/* Variables and functions */
 scalar_t__ RME32_IO_CONTROL_REGISTER ; 
 scalar_t__ RME32_IO_RESET_POS ; 
 int /*<<< orphan*/  RME32_WCR_START ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void snd_rme32_pcm_start(struct rme32 * rme32, int from_pause)
{
	if (!from_pause) {
		writel(0, rme32->iobase + RME32_IO_RESET_POS);
	}

	rme32->wcreg |= RME32_WCR_START;
	writel(rme32->wcreg, rme32->iobase + RME32_IO_CONTROL_REGISTER);
}