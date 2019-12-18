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
struct TYPE_4__ {TYPE_1__* gr; } ;
struct TYPE_3__ {int h; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL_ANOMALY ; 
 size_t SSP_PC ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_2__ known_regs ; 

void tr_unhandled(void)
{
	//FILE *f = fopen("tcache.bin", "wb");
	//fwrite(tcache, 1, (tcache_ptr - tcache)*4, f);
	//fclose(f);
	elprintf(EL_ANOMALY, "unhandled @ %04x\n", known_regs.gr[SSP_PC].h<<1);
	//exit(1);
}