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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  ir_tasklet; int /*<<< orphan*/  ir_command; } ;
struct av7110 {TYPE_1__ ir; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ir_handler(struct av7110 *av7110, u32 ircom)
{
	dprintk(4, "ir command = %08x\n", ircom);
	av7110->ir.ir_command = ircom;
	tasklet_schedule(&av7110->ir.ir_tasklet);
}