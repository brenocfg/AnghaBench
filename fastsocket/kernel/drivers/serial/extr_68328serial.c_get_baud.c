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
struct m68k_serial {size_t line; } ;
struct TYPE_2__ {unsigned short ubaud; } ;

/* Variables and functions */
 unsigned long GET_FIELD (unsigned short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UBAUD_DIVIDE ; 
 int /*<<< orphan*/  UBAUD_PRESCALER ; 
 TYPE_1__* uart_addr ; 

__attribute__((used)) static inline int get_baud(struct m68k_serial *ss)
{
	unsigned long result = 115200;
	unsigned short int baud = uart_addr[ss->line].ubaud;
	if (GET_FIELD(baud, UBAUD_PRESCALER) == 0x38) result = 38400;
	result >>= GET_FIELD(baud, UBAUD_DIVIDE);

	return result;
}