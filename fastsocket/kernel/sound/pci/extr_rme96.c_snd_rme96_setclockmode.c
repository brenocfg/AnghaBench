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
struct rme96 {scalar_t__ iobase; int /*<<< orphan*/  areg; int /*<<< orphan*/  wcreg; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RME96_AR_WSEL ; 
#define  RME96_CLOCKMODE_MASTER 130 
#define  RME96_CLOCKMODE_SLAVE 129 
#define  RME96_CLOCKMODE_WORDCLOCK 128 
 scalar_t__ RME96_IO_ADDITIONAL_REG ; 
 scalar_t__ RME96_IO_CONTROL_REGISTER ; 
 int /*<<< orphan*/  RME96_WCR_MASTER ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
snd_rme96_setclockmode(struct rme96 *rme96,
		       int mode)
{
	switch (mode) {
	case RME96_CLOCKMODE_SLAVE:
	        /* AutoSync */ 
		rme96->wcreg &= ~RME96_WCR_MASTER;
		rme96->areg &= ~RME96_AR_WSEL;
		break;
	case RME96_CLOCKMODE_MASTER:
	        /* Internal */
		rme96->wcreg |= RME96_WCR_MASTER;
		rme96->areg &= ~RME96_AR_WSEL;
		break;
	case RME96_CLOCKMODE_WORDCLOCK:
		/* Word clock is a master mode */
		rme96->wcreg |= RME96_WCR_MASTER; 
		rme96->areg |= RME96_AR_WSEL;
		break;
	default:
		return -EINVAL;
	}
	writel(rme96->wcreg, rme96->iobase + RME96_IO_CONTROL_REGISTER);
	writel(rme96->areg, rme96->iobase + RME96_IO_ADDITIONAL_REG);
	return 0;
}