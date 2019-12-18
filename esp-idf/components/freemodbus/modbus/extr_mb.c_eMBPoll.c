#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int eMBException ;
typedef  int eMBEventType ;
typedef  int /*<<< orphan*/  eMBErrorCode ;
typedef  int /*<<< orphan*/  USHORT ;
typedef  int UCHAR ;
struct TYPE_2__ {int ucFunctionCode; int (* pxHandler ) (int*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
#define  EV_EXECUTE 131 
#define  EV_FRAME_RECEIVED 130 
#define  EV_FRAME_SENT 129 
#define  EV_READY 128 
 int MB_ADDRESS_BROADCAST ; 
 int /*<<< orphan*/  MB_ASCII ; 
 int /*<<< orphan*/  MB_ASCII_TIMEOUT_WAIT_BEFORE_SEND_MS ; 
 int /*<<< orphan*/  MB_EILLSTATE ; 
 int /*<<< orphan*/  MB_ENOERR ; 
 int MB_EX_ILLEGAL_FUNCTION ; 
 int MB_EX_NONE ; 
 int MB_FUNC_ERROR ; 
 int MB_FUNC_HANDLERS_MAX ; 
 size_t MB_PDU_FUNC_OFF ; 
 scalar_t__ STATE_ENABLED ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  eMBCurrentMode ; 
 scalar_t__ eMBState ; 
 int /*<<< orphan*/  peMBFrameReceiveCur (int*,int**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  peMBFrameSendCur (int,int*,int /*<<< orphan*/ ) ; 
 int stub1 (int*,int /*<<< orphan*/ *) ; 
 int ucMBAddress ; 
 int /*<<< orphan*/  vMBPortTimersDelay (int /*<<< orphan*/ ) ; 
 TYPE_1__* xFuncHandlers ; 
 scalar_t__ xMBPortEventGet (int*) ; 
 int /*<<< orphan*/  xMBPortEventPost (int) ; 

eMBErrorCode
eMBPoll( void )
{
    static UCHAR   *ucMBFrame;
    static UCHAR    ucRcvAddress;
    static UCHAR    ucFunctionCode;
    static USHORT   usLength;
    static eMBException eException;

    int             i;
    eMBErrorCode    eStatus = MB_ENOERR;
    eMBEventType    eEvent;

    /* Check if the protocol stack is ready. */
    if( eMBState != STATE_ENABLED )
    {
        return MB_EILLSTATE;
    }

    /* Check if there is a event available. If not return control to caller.
     * Otherwise we will handle the event. */
    if( xMBPortEventGet( &eEvent ) == TRUE )
    {
        switch ( eEvent )
        {
        case EV_READY:
            break;

        case EV_FRAME_RECEIVED:
            eStatus = peMBFrameReceiveCur( &ucRcvAddress, &ucMBFrame, &usLength );
            if( eStatus == MB_ENOERR )
            {
                /* Check if the frame is for us. If not ignore the frame. */
                if( ( ucRcvAddress == ucMBAddress ) || ( ucRcvAddress == MB_ADDRESS_BROADCAST ) )
                {
                    ( void )xMBPortEventPost( EV_EXECUTE );
                }
            }
            break;

        case EV_EXECUTE:
            ucFunctionCode = ucMBFrame[MB_PDU_FUNC_OFF];
            eException = MB_EX_ILLEGAL_FUNCTION;
            for( i = 0; i < MB_FUNC_HANDLERS_MAX; i++ )
            {
                /* No more function handlers registered. Abort. */
                if( xFuncHandlers[i].ucFunctionCode == 0 )
                {
                    break;
                }
                else if( xFuncHandlers[i].ucFunctionCode == ucFunctionCode )
                {
                    eException = xFuncHandlers[i].pxHandler( ucMBFrame, &usLength );
                    break;
                }
            }

            /* If the request was not sent to the broadcast address we
             * return a reply. */
            if( ucRcvAddress != MB_ADDRESS_BROADCAST )
            {
                if( eException != MB_EX_NONE )
                {
                    /* An exception occurred. Build an error frame. */
                    usLength = 0;
                    ucMBFrame[usLength++] = ( UCHAR )( ucFunctionCode | MB_FUNC_ERROR );
                    ucMBFrame[usLength++] = eException;
                }
                if( ( eMBCurrentMode == MB_ASCII ) && MB_ASCII_TIMEOUT_WAIT_BEFORE_SEND_MS )
                {
                    vMBPortTimersDelay( MB_ASCII_TIMEOUT_WAIT_BEFORE_SEND_MS );
                }                
                eStatus = peMBFrameSendCur( ucMBAddress, ucMBFrame, usLength );
            }
            break;

        case EV_FRAME_SENT:
            break;
        }
    }
    return MB_ENOERR;
}