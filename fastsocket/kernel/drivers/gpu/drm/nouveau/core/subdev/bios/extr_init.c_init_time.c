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
typedef  int u16 ;
struct nvbios_init {scalar_t__ offset; struct nouveau_bios* bios; } ;
struct nouveau_bios {int dummy; } ;

/* Variables and functions */
 scalar_t__ init_exec (struct nvbios_init*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int nv_ro16 (struct nouveau_bios*,scalar_t__) ; 
 int /*<<< orphan*/  trace (char*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void
init_time(struct nvbios_init *init)
{
	struct nouveau_bios *bios = init->bios;
	u16 usec = nv_ro16(bios, init->offset + 1);

	trace("TIME\t0x%04x\n", usec);
	init->offset += 3;

	if (init_exec(init)) {
		if (usec < 1000)
			udelay(usec);
		else
			mdelay((usec + 900) / 1000);
	}
}