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
typedef  int /*<<< orphan*/  eMBErrorCode ;

/* Variables and functions */
 int /*<<< orphan*/  MB_EILLSTATE ; 
 int /*<<< orphan*/  MB_ENOERR ; 
 scalar_t__ STATE_DISABLED ; 
 scalar_t__ STATE_ENABLED ; 
 scalar_t__ eMBState ; 
 int /*<<< orphan*/  pvMBFrameStartCur () ; 

eMBErrorCode
eMBEnable( void )
{
    eMBErrorCode    eStatus = MB_ENOERR;

    if( eMBState == STATE_DISABLED )
    {
        /* Activate the protocol stack. */
        pvMBFrameStartCur(  );
        eMBState = STATE_ENABLED;
    }
    else
    {
        eStatus = MB_EILLSTATE;
    }
    return eStatus;
}