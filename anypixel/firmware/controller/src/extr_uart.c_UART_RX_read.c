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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_3__ {int configured; int /*<<< orphan*/  frame_available; int /*<<< orphan*/  rx_fifo; } ;
typedef  TYPE_1__ CONFIG_USART_ConfigState ;

/* Variables and functions */
 int FIFO_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ __LDREXH (int /*<<< orphan*/ *) ; 
 scalar_t__ __STREXH (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 

bool UART_RX_read(CONFIG_USART_ConfigState *cfg, char *outBuffer, uint16_t count) {
	bool retval;
	uint16_t workAvail;

	assert(cfg->configured == true);

    retval = FIFO_read(cfg->rx_fifo, (uint8_t*)outBuffer, count);
	if(retval) {
        /*cfg->frame_available -= count;
	    if(cfg->frame_available < 0)
	        cfg->frame_available = 0;*/
        // make sure writes to frame_available counter are thread safe
        do {
            workAvail = __LDREXH(&cfg->frame_available);
            if(workAvail < count)
                workAvail = 0;
            else
                workAvail -= count;
        } while( __STREXH(workAvail, &cfg->frame_available));


	}
	return retval;
}