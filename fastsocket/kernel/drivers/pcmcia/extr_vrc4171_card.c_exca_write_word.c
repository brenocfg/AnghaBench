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
typedef  int uint8_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_CONTROLLER_DATA ; 
 int /*<<< orphan*/  CARD_CONTROLLER_INDEX ; 
 int CARD_SLOTB ; 
 int CARD_SLOTB_OFFSET ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint16_t exca_write_word(int slot, uint8_t index, uint16_t data)
{
	if (slot == CARD_SLOTB)
		index += CARD_SLOTB_OFFSET;

	outb(index++, CARD_CONTROLLER_INDEX);
	outb(data, CARD_CONTROLLER_DATA);

	outb(index, CARD_CONTROLLER_INDEX);
	outb((uint8_t)(data >> 8), CARD_CONTROLLER_DATA);

	return data;
}