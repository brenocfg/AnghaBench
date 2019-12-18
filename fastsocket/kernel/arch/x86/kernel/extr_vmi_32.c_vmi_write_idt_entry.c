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
typedef  int /*<<< orphan*/  gate_desc ;
struct TYPE_2__ {int /*<<< orphan*/  (* write_idt_entry ) (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ vmi_ops ; 

__attribute__((used)) static void vmi_write_idt_entry(gate_desc *dt, int entry, const gate_desc *g)
{
	u32 *idt_entry = (u32 *)g;
	vmi_ops.write_idt_entry(dt, entry, idt_entry[0], idt_entry[1]);
}