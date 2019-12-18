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
typedef  int u8 ;
struct gameport {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg (char*,int) ; 
 int gameport_read (struct gameport*) ; 
 int gameport_time (struct gameport*,int) ; 

__attribute__((used)) static inline int poll_until(u8 onbits, u8 offbits, int u_sec, struct gameport* gp, u8 *data)
{
	int i, nloops;

	nloops = gameport_time(gp, u_sec);
	for (i = 0; i < nloops; i++) {
		*data = gameport_read(gp);
		if ((*data & onbits) == onbits &&
		    (~(*data) & offbits) == offbits)
			return 1;
	}
	dbg("gameport timed out after %d microseconds.\n", u_sec);
	return 0;
}