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
typedef  int /*<<< orphan*/  CHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EV_FRAME_SENT ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ STATE_RX_IDLE ; 
#define  STATE_TX_IDLE 129 
#define  STATE_TX_XMIT 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ eRcvState ; 
 int eSndState ; 
 int /*<<< orphan*/ * pucSndBufferCur ; 
 int /*<<< orphan*/  usSndBufferCount ; 
 int /*<<< orphan*/  vMBPortTimersEnable () ; 
 int /*<<< orphan*/  xMBPortEventPost (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xMBPortSerialPutByte (int /*<<< orphan*/ ) ; 

BOOL
xMBRTUTransmitFSM( void )
{
    BOOL xNeedPoll = FALSE;

    assert( eRcvState == STATE_RX_IDLE );

    switch ( eSndState )
    {
        /* We should not get a transmitter event if the transmitter is in
         * idle state.  */
    case STATE_TX_IDLE:
        break;

    case STATE_TX_XMIT:
        /* check if we are finished. */
        if( usSndBufferCount != 0 )
        {
            xMBPortSerialPutByte( ( CHAR )*pucSndBufferCur );
            pucSndBufferCur++;  /* next byte in sendbuffer. */
            usSndBufferCount--;
        }
        else
        {
            xMBPortEventPost( EV_FRAME_SENT );
            xNeedPoll = TRUE;
            eSndState = STATE_TX_IDLE;
            vMBPortTimersEnable(  );
        }
        break;
    }

    return xNeedPoll;
}