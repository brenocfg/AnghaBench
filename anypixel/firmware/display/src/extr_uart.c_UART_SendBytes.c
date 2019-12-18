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
typedef  int uint16_t ;
struct TYPE_3__ {int configured; int tx_buf_size; int TX_active; char* tx_buf; } ;
typedef  TYPE_1__ CONFIG_USART_ConfigState ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 

bool UART_SendBytes(CONFIG_USART_ConfigState *cfg, const char *buf, uint16_t length, bool block) {
	int i;

	assert(cfg->configured == true);
	assert(buf != NULL);
	assert(length <= cfg->tx_buf_size);

    if(block)
        while(cfg->TX_active);
    else
        if(cfg->TX_active)
            return false;

	cfg->TX_active = true;

    memcpy(cfg->tx_buf, buf, length);

	for(i = 0; i < length; i++)
		cfg->tx_buf[i] = buf[i];

    return true;
}