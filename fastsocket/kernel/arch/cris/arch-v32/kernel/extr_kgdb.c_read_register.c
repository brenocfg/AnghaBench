#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int srs; int /*<<< orphan*/  exs; int /*<<< orphan*/  wz; int /*<<< orphan*/  pid; int /*<<< orphan*/  bz; int /*<<< orphan*/  r0; } ;
struct TYPE_3__ {int /*<<< orphan*/  s0_0; } ;

/* Variables and functions */
 char ACR ; 
 char BZ ; 
 int E05 ; 
 char EXS ; 
 char PC ; 
 char PID ; 
 char R0 ; 
 char S0 ; 
 char S15 ; 
 char SRS ; 
 int SUCCESS ; 
 char VR ; 
 char WZ ; 
 TYPE_2__ reg ; 
 TYPE_1__ sreg ; 

__attribute__((used)) static int
read_register(char regno, unsigned int *valptr)
{
	int status = SUCCESS;

	/* We read the zero registers from the register struct (instead of just returning 0)
	   to catch errors. */

	if (regno >= R0 && regno <= ACR) {
		/* Consecutive 32-bit registers. */
		*valptr = *(unsigned int *)((char *)&reg.r0 + (regno - R0) * sizeof(unsigned int));

	} else if (regno == BZ || regno == VR) {
		/* Consecutive 8-bit registers. */
		*valptr = (unsigned int)(*(unsigned char *)
                                         ((char *)&reg.bz + (regno - BZ) * sizeof(char)));

	} else if (regno == PID) {
		/* 32-bit register. */
		*valptr =  *(unsigned int *)((char *)&reg.pid);

	} else if (regno == SRS) {
		/* 8-bit register. */
		*valptr = (unsigned int)(*(unsigned char *)((char *)&reg.srs));

	} else if (regno == WZ) {
		/* 16-bit register. */
		*valptr = (unsigned int)(*(unsigned short *)(char *)&reg.wz);

	} else if (regno >= EXS && regno <= PC) {
		/* Consecutive 32-bit registers. */
		*valptr = *(unsigned int *)((char *)&reg.exs + (regno - EXS) * sizeof(unsigned int));

	} else if (regno >= S0 && regno <= S15) {
		/* Consecutive 32-bit registers, located elsewhere. */
		*valptr = *(unsigned int *)((char *)&sreg.s0_0 + (reg.srs * 16 * sizeof(unsigned int)) + (regno - S0) * sizeof(unsigned int));

	} else {
		/* Non-existing register. */
		status = E05;
	}
	return status;

}