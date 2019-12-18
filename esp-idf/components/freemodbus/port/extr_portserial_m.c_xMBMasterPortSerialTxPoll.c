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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  scalar_t__ esp_err_t ;
typedef  int USHORT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ESP_OK ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  MB_PORT_CHECK (int,scalar_t__,char*) ; 
 scalar_t__ MB_SERIAL_BUF_SIZE ; 
 int /*<<< orphan*/  MB_SERIAL_TX_TOUT_TICKS ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ TRUE ; 
 scalar_t__ bTxStateEnabled ; 
 scalar_t__ pxMBMasterFrameCBTransmitterEmpty () ; 
 scalar_t__ uart_wait_tx_done (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucUartNumber ; 
 int /*<<< orphan*/  vMBMasterPortSerialEnable (scalar_t__,scalar_t__) ; 

BOOL xMBMasterPortSerialTxPoll(void)
{
    USHORT usCount = 0;
    BOOL bNeedPoll = FALSE;

    if( bTxStateEnabled ) {
        // Continue while all response bytes put in buffer or out of buffer
        while((bNeedPoll == FALSE) && (usCount++ < MB_SERIAL_BUF_SIZE)) {
            // Calls the modbus stack callback function to let it fill the UART transmit buffer.
            bNeedPoll = pxMBMasterFrameCBTransmitterEmpty( ); // calls callback xMBRTUTransmitFSM();
        }
        ESP_LOGD(TAG, "MB_TX_buffer sent: (%d) bytes.", (uint16_t)(usCount - 1));
        // Waits while UART sending the packet
        esp_err_t xTxStatus = uart_wait_tx_done(ucUartNumber, MB_SERIAL_TX_TOUT_TICKS);
        bTxStateEnabled = FALSE;
        vMBMasterPortSerialEnable( TRUE, FALSE );
        MB_PORT_CHECK((xTxStatus == ESP_OK), FALSE, "mb serial sent buffer failure.");
        return TRUE;
    }
    return FALSE;
}