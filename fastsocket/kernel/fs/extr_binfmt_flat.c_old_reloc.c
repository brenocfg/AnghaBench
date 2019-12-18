#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t type; scalar_t__ offset; } ;
struct TYPE_7__ {unsigned long value; TYPE_2__ reloc; } ;
typedef  TYPE_3__ flat_v2_reloc_t ;
struct TYPE_8__ {TYPE_1__* mm; } ;
struct TYPE_5__ {unsigned long end_data; scalar_t__ start_data; scalar_t__ start_code; } ;

/* Variables and functions */
#define  OLD_FLAT_RELOC_TYPE_BSS 130 
#define  OLD_FLAT_RELOC_TYPE_DATA 129 
#define  OLD_FLAT_RELOC_TYPE_TEXT 128 
 TYPE_4__* current ; 
 int /*<<< orphan*/  printk (char*,int,...) ; 

void old_reloc(unsigned long rl)
{
#ifdef DEBUG
	char *segment[] = { "TEXT", "DATA", "BSS", "*UNKNOWN*" };
#endif
	flat_v2_reloc_t	r;
	unsigned long *ptr;
	
	r.value = rl;
#if defined(CONFIG_COLDFIRE)
	ptr = (unsigned long *) (current->mm->start_code + r.reloc.offset);
#else
	ptr = (unsigned long *) (current->mm->start_data + r.reloc.offset);
#endif

#ifdef DEBUG
	printk("Relocation of variable at DATASEG+%x "
		"(address %p, currently %x) into segment %s\n",
		r.reloc.offset, ptr, (int)*ptr, segment[r.reloc.type]);
#endif
	
	switch (r.reloc.type) {
	case OLD_FLAT_RELOC_TYPE_TEXT:
		*ptr += current->mm->start_code;
		break;
	case OLD_FLAT_RELOC_TYPE_DATA:
		*ptr += current->mm->start_data;
		break;
	case OLD_FLAT_RELOC_TYPE_BSS:
		*ptr += current->mm->end_data;
		break;
	default:
		printk("BINFMT_FLAT: Unknown relocation type=%x\n", r.reloc.type);
		break;
	}

#ifdef DEBUG
	printk("Relocation became %x\n", (int)*ptr);
#endif
}