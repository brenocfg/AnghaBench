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
typedef  int /*<<< orphan*/  uint32_t ;
struct nouveau_therm {int dummy; } ;
struct nouveau_subdev {int dummy; } ;

/* Variables and functions */
 struct nouveau_therm* nouveau_therm (struct nouveau_subdev*) ; 
 int /*<<< orphan*/  nv_error (struct nouveau_therm*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_rd32 (struct nouveau_therm*,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nouveau_therm*,int,int) ; 

__attribute__((used)) static void
nv40_therm_intr(struct nouveau_subdev *subdev)
{
	struct nouveau_therm *therm = nouveau_therm(subdev);
	uint32_t stat = nv_rd32(therm, 0x1100);

	/* traitement */

	/* ack all IRQs */
	nv_wr32(therm, 0x1100, 0x70000);

	nv_error(therm, "THERM received an IRQ: stat = %x\n", stat);
}