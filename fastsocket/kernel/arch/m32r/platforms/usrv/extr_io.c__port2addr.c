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

/* Variables and functions */
 unsigned long NONCACHE_OFFSET ; 
 unsigned long UART0_IOEND ; 
 unsigned long UART0_IOSTART ; 
 unsigned long UART0_REGSTART ; 
 unsigned long UART1_IOEND ; 
 unsigned long UART1_IOSTART ; 
 unsigned long UART1_REGSTART ; 

__attribute__((used)) static inline void *_port2addr(unsigned long port)
{
#if defined(CONFIG_SERIAL_8250) || defined(CONFIG_SERIAL_8250_MODULE)
	if (port >= UART0_IOSTART && port <= UART0_IOEND)
		port = ((port - UART0_IOSTART) << 1) + UART0_REGSTART;
	else if (port >= UART1_IOSTART && port <= UART1_IOEND)
		port = ((port - UART1_IOSTART) << 1) + UART1_REGSTART;
#endif	/* CONFIG_SERIAL_8250 || CONFIG_SERIAL_8250_MODULE */
	return (void *)(port | (NONCACHE_OFFSET));
}