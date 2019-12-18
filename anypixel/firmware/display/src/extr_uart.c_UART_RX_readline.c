#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
struct TYPE_4__ {int configured; int /*<<< orphan*/  rx_fifo; } ;
typedef  TYPE_1__ CONFIG_USART_ConfigState ;

/* Variables and functions */
 scalar_t__ FIFO_available (int /*<<< orphan*/ ) ; 
 char FIFO_peek (int /*<<< orphan*/ ) ; 
 int FIFO_read_until (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,int) ; 
 int /*<<< orphan*/  UART_RX_read (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  assert (int) ; 

uint16_t UART_RX_readline(CONFIG_USART_ConfigState *cfg, char *outBuffer, uint16_t max) {
	int retval;

	assert(cfg->configured == true);

	retval = FIFO_read_until(cfg->rx_fifo, (uint8_t*)outBuffer, max-1, "\r\n", 2);
	if(retval == 0)
	    return 0;

	if(outBuffer[retval-1] == '\r') {
		retval--;
		// see if next character is a \n
		if( FIFO_available(cfg->rx_fifo)  &&  FIFO_peek(cfg->rx_fifo) == '\n' ) {
			// it is, so remove it from the queue
			char buf[2];
			UART_RX_read(cfg, buf, 1);
		}
	}
	if(outBuffer[retval-1] == '\n')
		retval--;
    outBuffer[retval++] = 0;
	return retval;
}