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
struct TYPE_3__ {int /*<<< orphan*/  p8; int /*<<< orphan*/  p4; int /*<<< orphan*/  p0; } ;
typedef  TYPE_1__ registers ;

/* Variables and functions */
 char CCR ; 
 int E05 ; 
 char MOF ; 
 char P0 ; 
 char P4 ; 
 char P8 ; 
 char PC ; 
 char R0 ; 
 int SUCCESS ; 
 char USP ; 
 char VR ; 
 int consistency_status ; 
 TYPE_1__ reg ; 

__attribute__((used)) static int
read_register (char regno, unsigned int *valptr)
{
	registers *current_reg = &reg;

	if (regno >= R0 && regno <= PC) {
		/* 32-bit register with simple offset. */
		*valptr = *(unsigned int *)((char *)current_reg + regno * sizeof(unsigned int));
                return SUCCESS;
	}
	else if (regno == P0 || regno == VR) {
		/* 8 bit register with complex offset. */
		*valptr = (unsigned int)(*(unsigned char *)
                                         ((char *)&(current_reg->p0) + (regno-P0) * sizeof(char)));
                return SUCCESS;
	}
	else if (regno == P4 || regno == CCR) {
		/* 16 bit register with complex offset. */
		*valptr = (unsigned int)(*(unsigned short *)
                                         ((char *)&(current_reg->p4) + (regno-P4) * sizeof(unsigned short)));
                return SUCCESS;
	}
	else if (regno >= MOF && regno <= USP) {
		/* 32 bit register with complex offset. */
		*valptr = *(unsigned int *)((char *)&(current_reg->p8)
                                            + (regno-P8) * sizeof(unsigned int));
                return SUCCESS;
	}
	else {
		/* Do not support nonexisting or unimplemented registers (P2, P3, and P6). */
		consistency_status = E05;
		return E05;
	}
}