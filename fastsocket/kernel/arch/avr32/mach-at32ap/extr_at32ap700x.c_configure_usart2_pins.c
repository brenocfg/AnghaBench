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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  AT32_GPIOF_PULLUP ; 
 int ATMEL_USART_CLK ; 
 int ATMEL_USART_CTS ; 
 int ATMEL_USART_RTS ; 
 int /*<<< orphan*/  PERIPH_B ; 
 int /*<<< orphan*/  PIOB ; 
 int /*<<< orphan*/  select_peripheral (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void configure_usart2_pins(int flags)
{
	u32 pin_mask = (1 << 26) | (1 << 27); /* RXD & TXD */
	if (flags & ATMEL_USART_RTS)	pin_mask |= (1 << 30);
	if (flags & ATMEL_USART_CTS)	pin_mask |= (1 << 29);
	if (flags & ATMEL_USART_CLK)	pin_mask |= (1 << 28);

	select_peripheral(PIOB, pin_mask, PERIPH_B, AT32_GPIOF_PULLUP);
}