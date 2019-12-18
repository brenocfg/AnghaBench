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
typedef  scalar_t__ UWORD ;
typedef  size_t UBYTE ;
typedef  int /*<<< orphan*/  ESC_FunctionType ;

/* Variables and functions */
 int /*<<< orphan*/  MEMORY_dPutByte (scalar_t__,size_t) ; 
 scalar_t__* esc_address ; 
 int /*<<< orphan*/ * esc_function ; 

void ESC_Add(UWORD address, UBYTE esc_code, ESC_FunctionType function)
{
	esc_address[esc_code] = address;
	esc_function[esc_code] = function;
	MEMORY_dPutByte(address, 0xf2);			/* ESC */
	MEMORY_dPutByte(address + 1, esc_code);	/* ESC CODE */
}