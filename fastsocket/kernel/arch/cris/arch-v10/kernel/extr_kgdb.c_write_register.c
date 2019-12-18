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
struct TYPE_3__ {int /*<<< orphan*/  ibr; int /*<<< orphan*/  ccr; } ;
typedef  TYPE_1__ registers ;

/* Variables and functions */
 int CCR ; 
 int E02 ; 
 int E05 ; 
 int IBR ; 
 int MOF ; 
 int P0 ; 
 int P4 ; 
 int P8 ; 
 int PC ; 
 int R0 ; 
 int SUCCESS ; 
 int USP ; 
 int VR ; 
 int /*<<< orphan*/  hex2mem (unsigned char*,char*,int) ; 
 TYPE_1__ reg ; 

__attribute__((used)) static int
write_register (int regno, char *val)
{
	int status = SUCCESS;
	registers *current_reg = &reg;

        if (regno >= R0 && regno <= PC) {
		/* 32-bit register with simple offset. */
		hex2mem ((unsigned char *)current_reg + regno * sizeof(unsigned int),
			 val, sizeof(unsigned int));
	}
        else if (regno == P0 || regno == VR || regno == P4 || regno == P8) {
		/* Do not support read-only registers. */
		status = E02;
	}
        else if (regno == CCR) {
		/* 16 bit register with complex offset. (P4 is read-only, P6 is not implemented, 
                   and P7 (MOF) is 32 bits in ETRAX 100LX. */
		hex2mem ((unsigned char *)&(current_reg->ccr) + (regno-CCR) * sizeof(unsigned short),
			 val, sizeof(unsigned short));
	}
	else if (regno >= MOF && regno <= USP) {
		/* 32 bit register with complex offset.  (P8 has been taken care of.) */
		hex2mem ((unsigned char *)&(current_reg->ibr) + (regno-IBR) * sizeof(unsigned int),
			 val, sizeof(unsigned int));
	} 
        else {
		/* Do not support nonexisting or unimplemented registers (P2, P3, and P6). */
		status = E05;
	}
	return status;
}