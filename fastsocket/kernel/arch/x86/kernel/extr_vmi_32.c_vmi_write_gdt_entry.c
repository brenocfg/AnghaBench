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
struct desc_struct {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* write_gdt_entry ) (struct desc_struct*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct desc_struct*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ vmi_ops ; 

__attribute__((used)) static void vmi_write_gdt_entry(struct desc_struct *dt, int entry,
				const void *desc, int type)
{
	u32 *gdt_entry = (u32 *)desc;
	vmi_ops.write_gdt_entry(dt, entry, gdt_entry[0], gdt_entry[1]);
}