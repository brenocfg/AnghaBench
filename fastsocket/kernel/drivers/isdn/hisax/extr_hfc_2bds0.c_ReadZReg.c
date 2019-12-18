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
typedef  int u_char ;
struct IsdnCardState {int dummy; } ;

/* Variables and functions */
 int HFCB_Z_HIGH ; 
 int HFCB_Z_LOW ; 
 int /*<<< orphan*/  HFCD_DATA ; 
 int ReadReg (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WaitNoBusy (struct IsdnCardState*) ; 

__attribute__((used)) static int
ReadZReg(struct IsdnCardState *cs, u_char reg)
{
	int val;

	WaitNoBusy(cs);
	val = 256 * ReadReg(cs, HFCD_DATA, reg | HFCB_Z_HIGH);
	WaitNoBusy(cs);
	val += ReadReg(cs, HFCD_DATA, reg | HFCB_Z_LOW);
	return (val);
}