#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int opened; void (* midi_input_intr ) (int,unsigned char) ;scalar_t__ disabled; } ;
typedef  TYPE_1__ uart401_devc ;
struct TYPE_7__ {scalar_t__ devc; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  enter_uart_mode (TYPE_1__*) ; 
 scalar_t__ input_avail (TYPE_1__*) ; 
 TYPE_3__** midi_devs ; 
 int /*<<< orphan*/  uart401_read (TYPE_1__*) ; 

__attribute__((used)) static int
uart401_open(int dev, int mode,
	     void            (*input) (int dev, unsigned char data),
	     void            (*output) (int dev)
)
{
	uart401_devc *devc = (uart401_devc *) midi_devs[dev]->devc;

	if (devc->opened)
		return -EBUSY;

	/* Flush the UART */
	
	while (input_avail(devc))
		uart401_read(devc);

	devc->midi_input_intr = input;
	devc->opened = mode;
	enter_uart_mode(devc);
	devc->disabled = 0;

	return 0;
}