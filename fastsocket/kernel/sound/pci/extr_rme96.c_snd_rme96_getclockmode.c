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
struct rme96 {int areg; int wcreg; } ;

/* Variables and functions */
 int RME96_AR_WSEL ; 
 int RME96_CLOCKMODE_MASTER ; 
 int RME96_CLOCKMODE_SLAVE ; 
 int RME96_CLOCKMODE_WORDCLOCK ; 
 int RME96_WCR_MASTER ; 

__attribute__((used)) static int
snd_rme96_getclockmode(struct rme96 *rme96)
{
	if (rme96->areg & RME96_AR_WSEL) {
		return RME96_CLOCKMODE_WORDCLOCK;
	}
	return (rme96->wcreg & RME96_WCR_MASTER) ? RME96_CLOCKMODE_MASTER :
		RME96_CLOCKMODE_SLAVE;
}