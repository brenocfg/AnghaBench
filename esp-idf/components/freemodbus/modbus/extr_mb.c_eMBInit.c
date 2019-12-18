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
typedef  int /*<<< orphan*/  eMBParity ;
typedef  int eMBMode ;
typedef  scalar_t__ eMBErrorCode ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  scalar_t__ UCHAR ;

/* Variables and functions */
 scalar_t__ MB_ADDRESS_BROADCAST ; 
 scalar_t__ MB_ADDRESS_MAX ; 
 scalar_t__ MB_ADDRESS_MIN ; 
#define  MB_ASCII 129 
 scalar_t__ MB_EINVAL ; 
 scalar_t__ MB_ENOERR ; 
 scalar_t__ MB_EPORTERR ; 
 int /*<<< orphan*/  MB_PORT_HAS_CLOSE ; 
#define  MB_RTU 128 
 int /*<<< orphan*/  STATE_DISABLED ; 
 scalar_t__ eMBASCIIInit (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eMBASCIIReceive ; 
 int /*<<< orphan*/  eMBASCIISend ; 
 int /*<<< orphan*/  eMBASCIIStart ; 
 int /*<<< orphan*/  eMBASCIIStop ; 
 int eMBCurrentMode ; 
 scalar_t__ eMBRTUInit (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eMBRTUReceive ; 
 int /*<<< orphan*/  eMBRTUSend ; 
 int /*<<< orphan*/  eMBRTUStart ; 
 int /*<<< orphan*/  eMBRTUStop ; 
 int /*<<< orphan*/  eMBState ; 
 int /*<<< orphan*/  peMBFrameReceiveCur ; 
 int /*<<< orphan*/  peMBFrameSendCur ; 
 int /*<<< orphan*/ * pvMBFrameCloseCur ; 
 int /*<<< orphan*/  pvMBFrameStartCur ; 
 int /*<<< orphan*/  pvMBFrameStopCur ; 
 int /*<<< orphan*/  pxMBFrameCBByteReceived ; 
 int /*<<< orphan*/  pxMBFrameCBTransmitterEmpty ; 
 int /*<<< orphan*/  pxMBPortCBTimerExpired ; 
 scalar_t__ ucMBAddress ; 
 int /*<<< orphan*/ * vMBPortClose ; 
 int /*<<< orphan*/  xMBASCIIReceiveFSM ; 
 int /*<<< orphan*/  xMBASCIITimerT1SExpired ; 
 int /*<<< orphan*/  xMBASCIITransmitFSM ; 
 int /*<<< orphan*/  xMBPortEventInit () ; 
 int /*<<< orphan*/  xMBRTUReceiveFSM ; 
 int /*<<< orphan*/  xMBRTUTimerT35Expired ; 
 int /*<<< orphan*/  xMBRTUTransmitFSM ; 

eMBErrorCode
eMBInit( eMBMode eMode, UCHAR ucSlaveAddress, UCHAR ucPort, ULONG ulBaudRate, eMBParity eParity )
{
    eMBErrorCode    eStatus = MB_ENOERR;

    /* check preconditions */
    if( ( ucSlaveAddress == MB_ADDRESS_BROADCAST ) ||
        ( ucSlaveAddress < MB_ADDRESS_MIN ) || ( ucSlaveAddress > MB_ADDRESS_MAX ) )
    {
        eStatus = MB_EINVAL;
    }
    else
    {
        ucMBAddress = ucSlaveAddress;

        switch ( eMode )
        {
#if MB_SLAVE_RTU_ENABLED > 0
        case MB_RTU:
            pvMBFrameStartCur = eMBRTUStart;
            pvMBFrameStopCur = eMBRTUStop;
            peMBFrameSendCur = eMBRTUSend;
            peMBFrameReceiveCur = eMBRTUReceive;
            pvMBFrameCloseCur = MB_PORT_HAS_CLOSE ? vMBPortClose : NULL;
            pxMBFrameCBByteReceived = xMBRTUReceiveFSM;
            pxMBFrameCBTransmitterEmpty = xMBRTUTransmitFSM;
            pxMBPortCBTimerExpired = xMBRTUTimerT35Expired;

            eStatus = eMBRTUInit( ucMBAddress, ucPort, ulBaudRate, eParity );
            break;
#endif
#if MB_SLAVE_ASCII_ENABLED > 0
        case MB_ASCII:
            pvMBFrameStartCur = eMBASCIIStart;
            pvMBFrameStopCur = eMBASCIIStop;
            peMBFrameSendCur = eMBASCIISend;
            peMBFrameReceiveCur = eMBASCIIReceive;
            pvMBFrameCloseCur = MB_PORT_HAS_CLOSE ? vMBPortClose : NULL;
            pxMBFrameCBByteReceived = xMBASCIIReceiveFSM;
            pxMBFrameCBTransmitterEmpty = xMBASCIITransmitFSM;
            pxMBPortCBTimerExpired = xMBASCIITimerT1SExpired;

            eStatus = eMBASCIIInit( ucMBAddress, ucPort, ulBaudRate, eParity );
            break;
#endif
        default:
            eStatus = MB_EINVAL;
        }

        if( eStatus == MB_ENOERR )
        {
            if( !xMBPortEventInit(  ) )
            {
                /* port dependent event module initalization failed. */
                eStatus = MB_EPORTERR;
            }
            else
            {
                eMBCurrentMode = eMode;
                eMBState = STATE_DISABLED;
            }
        }
    }
    return eStatus;
}