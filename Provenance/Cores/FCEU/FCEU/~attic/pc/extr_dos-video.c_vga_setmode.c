#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  regs ;
struct TYPE_5__ {int ax; } ;
struct TYPE_6__ {TYPE_1__ x; } ;
typedef  TYPE_2__ __dpmi_regs ;

/* Variables and functions */
 int /*<<< orphan*/  __dpmi_int (int,TYPE_2__*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vga_setmode(int mode)
{
 __dpmi_regs regs;

 memset(&regs,0,sizeof(regs));
 regs.x.ax=mode;

 __dpmi_int(0x10,&regs);
}