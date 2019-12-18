#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  addr; } ;
struct TYPE_12__ {scalar_t__ CMDGRDA; } ;
struct TYPE_11__ {void* value; } ;
struct TYPE_10__ {void* value; } ;
struct TYPE_9__ {void* value; } ;
struct TYPE_8__ {void* value; } ;

/* Variables and functions */
 void* T1ReadWord (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Vdp1Ram ; 
 int /*<<< orphan*/  Vdp1ReadCommand (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__* Vdp1Regs ; 
 TYPE_5__ cmd ; 
 TYPE_4__ gouraudA ; 
 TYPE_3__ gouraudB ; 
 TYPE_2__ gouraudC ; 
 TYPE_1__ gouraudD ; 

__attribute__((used)) static void gouraudTable(void)
{
	int gouraudTableAddress;

  Vdp1ReadCommand(&cmd, Vdp1Regs->addr, Vdp1Ram);

	gouraudTableAddress = (((unsigned int)cmd.CMDGRDA) << 3);

	gouraudA.value = T1ReadWord(Vdp1Ram,gouraudTableAddress);
	gouraudB.value = T1ReadWord(Vdp1Ram,gouraudTableAddress+2);
	gouraudC.value = T1ReadWord(Vdp1Ram,gouraudTableAddress+4);
	gouraudD.value = T1ReadWord(Vdp1Ram,gouraudTableAddress+6);
}