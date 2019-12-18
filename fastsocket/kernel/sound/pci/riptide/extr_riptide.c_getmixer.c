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
union cmdret {unsigned short* retwords; } ;
struct cmdif {int dummy; } ;

/* Variables and functions */
 union cmdret CMDRET_ZERO ; 
 int EIO ; 
 scalar_t__ SEND_RDGV (struct cmdif*,short,short,union cmdret*) ; 
 int /*<<< orphan*/  snd_printdd (char*,short,unsigned short,unsigned short) ; 

__attribute__((used)) static int
getmixer(struct cmdif *cif, short num, unsigned short *rval,
	 unsigned short *lval)
{
	union cmdret rptr = CMDRET_ZERO;

	if (SEND_RDGV(cif, num, num, &rptr) && SEND_RDGV(cif, num, num, &rptr))
		return -EIO;
	*rval = rptr.retwords[0];
	*lval = rptr.retwords[1];
	snd_printdd("got mixer %d: 0x%d 0x%d\n", num, *rval, *lval);
	return 0;
}