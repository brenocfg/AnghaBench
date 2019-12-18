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
struct tsc2007 {int dummy; } ;
struct ts_event {void* z2; void* z1; void* x; void* y; } ;

/* Variables and functions */
 int /*<<< orphan*/  PWRDOWN ; 
 int /*<<< orphan*/  READ_X ; 
 int /*<<< orphan*/  READ_Y ; 
 int /*<<< orphan*/  READ_Z1 ; 
 int /*<<< orphan*/  READ_Z2 ; 
 void* tsc2007_xfer (struct tsc2007*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tsc2007_read_values(struct tsc2007 *tsc, struct ts_event *tc)
{
	/* y- still on; turn on only y+ (and ADC) */
	tc->y = tsc2007_xfer(tsc, READ_Y);

	/* turn y- off, x+ on, then leave in lowpower */
	tc->x = tsc2007_xfer(tsc, READ_X);

	/* turn y+ off, x- on; we'll use formula #1 */
	tc->z1 = tsc2007_xfer(tsc, READ_Z1);
	tc->z2 = tsc2007_xfer(tsc, READ_Z2);

	/* Prepare for next touch reading - power down ADC, enable PENIRQ */
	tsc2007_xfer(tsc, PWRDOWN);
}