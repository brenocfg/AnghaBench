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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct module {int dummy; } ;
struct m68k_fixup_info {int type; scalar_t__ addr; } ;

/* Variables and functions */
#define  m68k_fixup_memoffset 129 
#define  m68k_fixup_vnode_shift 128 
 int /*<<< orphan*/  m68k_memoffset ; 
 int /*<<< orphan*/  m68k_virt_to_node_shift ; 

void module_fixup(struct module *mod, struct m68k_fixup_info *start,
		  struct m68k_fixup_info *end)
{
	struct m68k_fixup_info *fixup;

	for (fixup = start; fixup < end; fixup++) {
		switch (fixup->type) {
		case m68k_fixup_memoffset:
			*(u32 *)fixup->addr = m68k_memoffset;
			break;
		case m68k_fixup_vnode_shift:
			*(u16 *)fixup->addr += m68k_virt_to_node_shift;
			break;
		}
	}
}