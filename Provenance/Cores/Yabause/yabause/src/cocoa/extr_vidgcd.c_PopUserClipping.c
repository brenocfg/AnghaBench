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
struct TYPE_2__ {int /*<<< orphan*/  systemclipY2; int /*<<< orphan*/  systemclipY1; int /*<<< orphan*/  systemclipX2; int /*<<< orphan*/  systemclipX1; } ;

/* Variables and functions */
 TYPE_1__* Vdp1Regs ; 
 int /*<<< orphan*/  vdp1clipxend ; 
 int /*<<< orphan*/  vdp1clipxstart ; 
 int /*<<< orphan*/  vdp1clipyend ; 
 int /*<<< orphan*/  vdp1clipystart ; 

__attribute__((used)) static void PopUserClipping(void)
{
   vdp1clipxstart = Vdp1Regs->systemclipX1;
   vdp1clipxend = Vdp1Regs->systemclipX2;
   vdp1clipystart = Vdp1Regs->systemclipY1;
   vdp1clipyend = Vdp1Regs->systemclipY2;
}