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
struct TYPE_4__ {int srs; int /*<<< orphan*/  exs; int /*<<< orphan*/  pid; int /*<<< orphan*/  r0; } ;
struct TYPE_3__ {int /*<<< orphan*/  s0_0; } ;

/* Variables and functions */
 int ACR ; 
 int BZ ; 
 int DZ ; 
 int E02 ; 
 int E05 ; 
 int EXS ; 
 int PC ; 
 int PID ; 
 int R0 ; 
 int S0 ; 
 int S15 ; 
 int SPC ; 
 int SRS ; 
 int SUCCESS ; 
 int VR ; 
 int WZ ; 
 int /*<<< orphan*/  hex2mem (unsigned char*,char*,int) ; 
 TYPE_2__ reg ; 
 TYPE_1__ sreg ; 

__attribute__((used)) static int
write_register(int regno, char *val)
{
	int status = SUCCESS;

        if (regno >= R0 && regno <= ACR) {
		/* Consecutive 32-bit registers. */
		hex2mem((unsigned char *)&reg.r0 + (regno - R0) * sizeof(unsigned int),
			val, sizeof(unsigned int));

	} else if (regno == BZ || regno == VR || regno == WZ || regno == DZ) {
		/* Read-only registers. */
		status = E02;

	} else if (regno == PID) {
		/* 32-bit register. (Even though we already checked SRS and WZ, we cannot
		   combine this with the EXS - SPC write since SRS and WZ have different size.) */
		hex2mem((unsigned char *)&reg.pid, val, sizeof(unsigned int));

	} else if (regno == SRS) {
		/* 8-bit register. */
		hex2mem((unsigned char *)&reg.srs, val, sizeof(unsigned char));

	} else if (regno >= EXS && regno <= SPC) {
		/* Consecutive 32-bit registers. */
		hex2mem((unsigned char *)&reg.exs + (regno - EXS) * sizeof(unsigned int),
			 val, sizeof(unsigned int));

       } else if (regno == PC) {
               /* Pseudo-register. Treat as read-only. */
               status = E02;

       } else if (regno >= S0 && regno <= S15) {
               /* 32-bit registers. */
               hex2mem((unsigned char *)&sreg.s0_0 + (reg.srs * 16 * sizeof(unsigned int)) + (regno - S0) * sizeof(unsigned int), val, sizeof(unsigned int));
	} else {
		/* Non-existing register. */
		status = E05;
	}
	return status;
}