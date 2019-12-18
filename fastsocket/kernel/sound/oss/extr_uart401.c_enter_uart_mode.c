#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ input_byte; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ uart401_devc ;

/* Variables and functions */
 scalar_t__ MPU_ACK ; 
 int /*<<< orphan*/  UART_MODE_ON ; 
 scalar_t__ input_avail (TYPE_1__*) ; 
 int /*<<< orphan*/  output_ready (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  uart401_cmd (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ uart401_read (TYPE_1__*) ; 

__attribute__((used)) static void enter_uart_mode(uart401_devc * devc)
{
	int ok, timeout;
	unsigned long flags;

	spin_lock_irqsave(&devc->lock,flags);	
	for (timeout = 30000; timeout > 0 && !output_ready(devc); timeout--);

	devc->input_byte = 0;
	uart401_cmd(devc, UART_MODE_ON);

	ok = 0;
	for (timeout = 50000; timeout > 0 && !ok; timeout--)
		if (devc->input_byte == MPU_ACK)
			ok = 1;
		else if (input_avail(devc))
			if (uart401_read(devc) == MPU_ACK)
				ok = 1;

	spin_unlock_irqrestore(&devc->lock,flags);
}