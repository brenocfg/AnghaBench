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
struct TYPE_3__ {int slot_no; } ;
typedef  TYPE_1__ ecard_t ;
typedef  int card_type_t ;
typedef  int card_speed_t ;

/* Variables and functions */
#define  ECARD_EASI 130 
 int ECARD_FAST ; 
#define  ECARD_IOC 129 
#define  ECARD_MEMC 128 
 int /*<<< orphan*/  IOMD_ECTCR ; 
 int /*<<< orphan*/  IO_EC_EASI_BASE ; 
 int /*<<< orphan*/  IO_EC_IOC4_BASE ; 
 int /*<<< orphan*/  IO_EC_IOC_BASE ; 
 unsigned int IO_EC_MEMC8_BASE ; 
 int /*<<< orphan*/  IO_EC_MEMC_BASE ; 
 int ectcr ; 
 int /*<<< orphan*/  iomd_writeb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int __ecard_address(ecard_t *ec, card_type_t type, card_speed_t speed)
{
	unsigned long address = 0;
	int slot = ec->slot_no;

	if (ec->slot_no == 8)
		return IO_EC_MEMC8_BASE;

	ectcr &= ~(1 << slot);

	switch (type) {
	case ECARD_MEMC:
		if (slot < 4)
			address = IO_EC_MEMC_BASE + (slot << 12);
		break;

	case ECARD_IOC:
		if (slot < 4)
			address = IO_EC_IOC_BASE + (slot << 12);
#ifdef IO_EC_IOC4_BASE
		else
			address = IO_EC_IOC4_BASE + ((slot - 4) << 12);
#endif
		if (address)
			address +=  speed << 17;
		break;

#ifdef IO_EC_EASI_BASE
	case ECARD_EASI:
		address = IO_EC_EASI_BASE + (slot << 22);
		if (speed == ECARD_FAST)
			ectcr |= 1 << slot;
		break;
#endif
	default:
		break;
	}

#ifdef IOMD_ECTCR
	iomd_writeb(ectcr, IOMD_ECTCR);
#endif
	return address;
}