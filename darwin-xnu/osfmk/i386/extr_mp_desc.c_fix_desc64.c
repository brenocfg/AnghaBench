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
typedef  void* uint8_t ;
typedef  void* uint32_t ;
typedef  void* uint16_t ;
struct real_gate64 {int selector16; int IST; int access8; void* offset_top32; void* offset_high16; void* offset_low16; } ;
struct real_descriptor64 {int limit_low16; int access8; int limit_high4; int granularity4; void* base_top32; void* base_high8; void* base_med8; void* base_low16; } ;
struct fake_descriptor64 {int access; int offset64; int lim_or_seg; int size_or_IST; } ;
typedef  int /*<<< orphan*/  real ;

/* Variables and functions */
#define  ACC_CALL_GATE 130 
#define  ACC_INTR_GATE 129 
#define  ACC_TRAP_GATE 128 
 int ACC_TYPE ; 
 int /*<<< orphan*/  bcopy (void*,void*,int) ; 
 int /*<<< orphan*/  bzero (void*,int) ; 

void
fix_desc64(void *descp, int count)
{
	struct fake_descriptor64	*fakep;
	union {
		struct real_gate64		gate;
		struct real_descriptor64	desc;
	}				real;
	int				i;

	fakep = (struct fake_descriptor64 *) descp;
	
	for (i = 0; i < count; i++, fakep++) {
		/*
		 * Construct the real decriptor locally.
		 */

		bzero((void *) &real, sizeof(real));

		switch (fakep->access & ACC_TYPE) {
		case 0:
			break;
		case ACC_CALL_GATE:
		case ACC_INTR_GATE:
		case ACC_TRAP_GATE:
			real.gate.offset_low16 = (uint16_t)(fakep->offset64 & 0xFFFF);
			real.gate.selector16 = fakep->lim_or_seg & 0xFFFF;
			real.gate.IST = fakep->size_or_IST & 0x7;
			real.gate.access8 = fakep->access;
			real.gate.offset_high16 = (uint16_t)((fakep->offset64>>16) & 0xFFFF);
			real.gate.offset_top32 = (uint32_t)(fakep->offset64>>32);
			break;
		default:	/* Otherwise */
			real.desc.limit_low16 = fakep->lim_or_seg & 0xFFFF;
			real.desc.base_low16 = (uint16_t)(fakep->offset64 & 0xFFFF);
			real.desc.base_med8 = (uint8_t)((fakep->offset64 >> 16) & 0xFF);
			real.desc.access8 = fakep->access;
			real.desc.limit_high4 = (fakep->lim_or_seg >> 16) & 0xFF;
			real.desc.granularity4 = fakep->size_or_IST;
			real.desc.base_high8 = (uint8_t)((fakep->offset64 >> 24) & 0xFF);
			real.desc.base_top32 = (uint32_t)(fakep->offset64>>32);
		}

		/*
		 * Now copy back over the fake structure.
		 */
		bcopy((void *) &real, (void *) fakep, sizeof(real));
	}
}