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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int data_bits; int parity; int rx_flow_ctrl_thresh; int /*<<< orphan*/  flow_ctrl; int /*<<< orphan*/  stop_bits; int /*<<< orphan*/  baud_rate; } ;
typedef  TYPE_1__ uart_config_t ;
typedef  scalar_t__ esp_err_t ;
typedef  int eMBParity ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  int UCHAR ;
typedef  scalar_t__ BaseType_t ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ESP_OK ; 
 int FALSE ; 
#define  MB_PAR_EVEN 130 
#define  MB_PAR_NONE 129 
#define  MB_PAR_ODD 128 
 int /*<<< orphan*/  MB_PORT_CHECK (int,int,char*,...) ; 
 int /*<<< orphan*/  MB_PORT_SERIAL_ISR_FLAG ; 
 int /*<<< orphan*/  MB_QUEUE_LENGTH ; 
 int /*<<< orphan*/  MB_SERIAL_BUF_SIZE ; 
 int /*<<< orphan*/  MB_SERIAL_TASK_PRIO ; 
 int /*<<< orphan*/  MB_SERIAL_TASK_STACK_SIZE ; 
 int /*<<< orphan*/  MB_SERIAL_TOUT ; 
 int /*<<< orphan*/  TRUE ; 
 int UART_DATA_5_BITS ; 
 int UART_DATA_6_BITS ; 
 int UART_DATA_7_BITS ; 
 int UART_DATA_8_BITS ; 
 int /*<<< orphan*/  UART_HW_FLOWCTRL_DISABLE ; 
 int UART_PARITY_DISABLE ; 
 int UART_PARITY_EVEN ; 
 int UART_PARITY_ODD ; 
 int /*<<< orphan*/  UART_STOP_BITS_1 ; 
 scalar_t__ pdPASS ; 
 scalar_t__ uart_driver_install (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ uart_param_config (int,TYPE_1__*) ; 
 scalar_t__ uart_set_rx_timeout (int,int /*<<< orphan*/ ) ; 
 int ucUartNumber ; 
 scalar_t__ uiRxBufferPos ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vTaskSuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vUartTask ; 
 int /*<<< orphan*/  xMbTaskHandle ; 
 int /*<<< orphan*/  xMbUartQueue ; 
 scalar_t__ xTaskCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

BOOL xMBPortSerialInit(UCHAR ucPORT, ULONG ulBaudRate,
                        UCHAR ucDataBits, eMBParity eParity)
{
    esp_err_t xErr = ESP_OK;
    MB_PORT_CHECK((eParity <= MB_PAR_EVEN), FALSE, "mb serial set parity failure.");
    // Set communication port number
    ucUartNumber = ucPORT;
    // Configure serial communication parameters
    UCHAR ucParity = UART_PARITY_DISABLE;
    UCHAR ucData = UART_DATA_8_BITS;
    switch(eParity){
        case MB_PAR_NONE:
            ucParity = UART_PARITY_DISABLE;
            break;
        case MB_PAR_ODD:
            ucParity = UART_PARITY_ODD;
            break;
        case MB_PAR_EVEN:
            ucParity = UART_PARITY_EVEN;
            break;
    }
    switch(ucDataBits){
        case 5:
            ucData = UART_DATA_5_BITS;
            break;
        case 6:
            ucData = UART_DATA_6_BITS;
            break;
        case 7:
            ucData = UART_DATA_7_BITS;
            break;
        case 8:
            ucData = UART_DATA_8_BITS;
            break;
        default:
            ucData = UART_DATA_8_BITS;
            break;
    }
    uart_config_t xUartConfig = {
        .baud_rate = ulBaudRate,
        .data_bits = ucData,
        .parity = ucParity,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .rx_flow_ctrl_thresh = 2,
    };
    // Set UART config
    xErr = uart_param_config(ucUartNumber, &xUartConfig);
    MB_PORT_CHECK((xErr == ESP_OK),
            FALSE, "mb config failure, uart_param_config() returned (0x%x).", (uint32_t)xErr);
    // Install UART driver, and get the queue.
    xErr = uart_driver_install(ucUartNumber, MB_SERIAL_BUF_SIZE, MB_SERIAL_BUF_SIZE,
                                    MB_QUEUE_LENGTH, &xMbUartQueue, MB_PORT_SERIAL_ISR_FLAG);
    MB_PORT_CHECK((xErr == ESP_OK), FALSE,
            "mb serial driver failure, uart_driver_install() returned (0x%x).", (uint32_t)xErr);
#ifndef MB_TIMER_PORT_ENABLED
    // Set timeout for TOUT interrupt (T3.5 modbus time)
    xErr = uart_set_rx_timeout(ucUartNumber, MB_SERIAL_TOUT);
    MB_PORT_CHECK((xErr == ESP_OK), FALSE,
            "mb serial set rx timeout failure, uart_set_rx_timeout() returned (0x%x).", (uint32_t)xErr);
#endif
    // Create a task to handle UART events
    BaseType_t xStatus = xTaskCreate(vUartTask, "uart_queue_task", MB_SERIAL_TASK_STACK_SIZE,
                                        NULL, MB_SERIAL_TASK_PRIO, &xMbTaskHandle);
    if (xStatus != pdPASS) {
        vTaskDelete(xMbTaskHandle);
        // Force exit from function with failure
        MB_PORT_CHECK(FALSE, FALSE,
                "mb stack serial task creation error. xTaskCreate() returned (0x%x).",
                (uint32_t)xStatus);
    } else {
        vTaskSuspend(xMbTaskHandle); // Suspend serial task while stack is not started
    }
    uiRxBufferPos = 0;
    return TRUE;
}