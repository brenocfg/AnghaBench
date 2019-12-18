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
struct TYPE_2__ {scalar_t__ iram_rom; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL_ANOMALY ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int* iram_context_map ; 
 int /*<<< orphan*/  rPC ; 
 TYPE_1__* svp ; 

int ssp_get_iram_context(void)
{
	unsigned char *ir = (unsigned char *)svp->iram_rom;
	int val1, val = ir[0x083^1] + ir[0x4FA^1] + ir[0x5F7^1] + ir[0x47B^1];
	val1 = iram_context_map[(val>>1)&0x3f];

	if (val1 == 0) {
		elprintf(EL_ANOMALY, "svp: iram ctx val: %02x PC=%04x\n", (val>>1)&0x3f, rPC);
		//debug_dump2file(name, svp->iram_rom, 0x800);
		//exit(1);
	}
	return val1;
}