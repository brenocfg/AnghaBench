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
struct mgsl_struct {int loopmode_insert_requested; int cmr_value; } ;

/* Variables and functions */
 int BIT13 ; 
 int /*<<< orphan*/  CMR ; 
 int /*<<< orphan*/  RICR ; 
 int RXSTATUS_ABORT_RECEIVED ; 
 int usc_InReg (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_OutReg (struct mgsl_struct*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void usc_loopmode_insert_request( struct mgsl_struct * info )
{
 	info->loopmode_insert_requested = true;
 
 	/* enable RxAbort irq. On next RxAbort, clear CMR:13 to
 	 * begin repeating TxData on RxData (complete insertion)
	 */
 	usc_OutReg( info, RICR, 
		(usc_InReg( info, RICR ) | RXSTATUS_ABORT_RECEIVED ) );
		
	/* set CMR:13 to insert into loop on next GoAhead (RxAbort) */
	info->cmr_value |= BIT13;
 	usc_OutReg(info, CMR, info->cmr_value);
}