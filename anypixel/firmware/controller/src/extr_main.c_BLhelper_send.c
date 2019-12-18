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
struct TYPE_2__ {int /*<<< orphan*/  a; } ;

/* Variables and functions */
 int /*<<< orphan*/  Delay (int) ; 
 size_t PANEL_NE ; 
 size_t PANEL_NW ; 
 size_t PANEL_SE ; 
 size_t PANEL_SW ; 
 int /*<<< orphan*/  UART_SendBytes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  USART_NE ; 
 int /*<<< orphan*/  USART_NW ; 
 int /*<<< orphan*/  USART_SE ; 
 int /*<<< orphan*/  USART_SW ; 
 int /*<<< orphan*/  handle_feedback (int /*<<< orphan*/ ,size_t) ; 
 TYPE_1__* ledpackets ; 
 int /*<<< orphan*/ * usarts ; 

__attribute__((used)) static void BLhelper_send() {
    UART_SendBytes(&usarts[3], ledpackets[PANEL_NW].a, sizeof(ledpackets[PANEL_NW].a));
    UART_SendBytes(&usarts[2], ledpackets[PANEL_NW].a, sizeof(ledpackets[PANEL_NW].a));
    UART_SendBytes(&usarts[1], ledpackets[PANEL_NW].a, sizeof(ledpackets[PANEL_NW].a));
    UART_SendBytes(&usarts[0], ledpackets[PANEL_NW].a, sizeof(ledpackets[PANEL_NW].a));
    Delay(1000);
    handle_feedback(USART_NW, PANEL_NW);
    handle_feedback(USART_SW, PANEL_SW);
    handle_feedback(USART_SE, PANEL_SE);
    handle_feedback(USART_NE, PANEL_NE);
}