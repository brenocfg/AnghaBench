#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  c_iflag; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICRNL ; 
 int /*<<< orphan*/  TCSETA ; 
 TYPE_1__ Terminal ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

void 
nl()
{
	int value;

#ifdef SYS5
	Terminal.c_iflag |= ICRNL;	/* enable carriage-return to line-feed mapping	*/
	value = ioctl(0, TCSETA, &Terminal);	/* set characteristics	*/
#endif
}