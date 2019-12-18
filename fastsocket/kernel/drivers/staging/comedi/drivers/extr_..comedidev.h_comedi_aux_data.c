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
 int /*<<< orphan*/  BUG_ON (int) ; 
 size_t COMEDI_DEVCONF_AUX_DATA0_LENGTH ; 
 size_t COMEDI_DEVCONF_AUX_DATA1_LENGTH ; 
 size_t COMEDI_DEVCONF_AUX_DATA2_LENGTH ; 
 size_t COMEDI_DEVCONF_AUX_DATA_HI ; 
 size_t COMEDI_DEVCONF_AUX_DATA_LO ; 

__attribute__((used)) static inline void *comedi_aux_data(int options[], int n)
{
	unsigned long address;
	unsigned long addressLow;
	int bit_shift;
	if (sizeof(int) >= sizeof(void *))
		address = options[COMEDI_DEVCONF_AUX_DATA_LO];
	else {
		address = options[COMEDI_DEVCONF_AUX_DATA_HI];
		bit_shift = sizeof(int) * 8;
		address <<= bit_shift;
		addressLow = options[COMEDI_DEVCONF_AUX_DATA_LO];
		addressLow &= (1UL << bit_shift) - 1;
		address |= addressLow;
	}
	if (n >= 1)
		address += options[COMEDI_DEVCONF_AUX_DATA0_LENGTH];
	if (n >= 2)
		address += options[COMEDI_DEVCONF_AUX_DATA1_LENGTH];
	if (n >= 3)
		address += options[COMEDI_DEVCONF_AUX_DATA2_LENGTH];
	BUG_ON(n > 3);
	return (void *)address;
}