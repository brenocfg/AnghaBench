#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct m68k_serial {size_t line; } ;
struct TYPE_4__ {int w; } ;
struct TYPE_5__ {TYPE_1__ utx; } ;
typedef  TYPE_2__ m68328_uart ;

/* Variables and functions */
 int UTX_CTS_STAT ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  put_user (unsigned char,unsigned int*) ; 
 TYPE_2__* uart_addr ; 

__attribute__((used)) static int get_lsr_info(struct m68k_serial * info, unsigned int *value)
{
#ifdef CONFIG_SERIAL_68328_RTS_CTS
	m68328_uart *uart = &uart_addr[info->line];
#endif
	unsigned char status;
	unsigned long flags;

	local_irq_save(flags);
#ifdef CONFIG_SERIAL_68328_RTS_CTS
	status = (uart->utx.w & UTX_CTS_STAT) ? 1 : 0;
#else
	status = 0;
#endif
	local_irq_restore(flags);
	put_user(status,value);
	return 0;
}