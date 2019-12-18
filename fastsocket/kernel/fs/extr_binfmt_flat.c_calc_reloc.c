#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct lib_info {TYPE_1__* lib_list; } ;
struct TYPE_5__ {int comm; } ;
struct TYPE_4__ {scalar_t__ build_date; unsigned long start_brk; unsigned long start_data; unsigned long start_code; unsigned long text_len; int /*<<< orphan*/  loaded; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_VALUE (int /*<<< orphan*/ ) ; 
 int MAX_SHARED_LIBS ; 
 unsigned long RELOC_FAILED ; 
 int /*<<< orphan*/  SIGSEGV ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  flat_reloc_valid (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  load_flat_shared_library (int,struct lib_info*) ; 
 int /*<<< orphan*/  printk (char*,int,...) ; 
 int /*<<< orphan*/  send_sig (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long
calc_reloc(unsigned long r, struct lib_info *p, int curid, int internalp)
{
	unsigned long addr;
	int id;
	unsigned long start_brk;
	unsigned long start_data;
	unsigned long text_len;
	unsigned long start_code;

#ifdef CONFIG_BINFMT_SHARED_FLAT
	if (r == 0)
		id = curid;	/* Relocs of 0 are always self referring */
	else {
		id = (r >> 24) & 0xff;	/* Find ID for this reloc */
		r &= 0x00ffffff;	/* Trim ID off here */
	}
	if (id >= MAX_SHARED_LIBS) {
		printk("BINFMT_FLAT: reference 0x%x to shared library %d",
				(unsigned) r, id);
		goto failed;
	}
	if (curid != id) {
		if (internalp) {
			printk("BINFMT_FLAT: reloc address 0x%x not in same module "
					"(%d != %d)", (unsigned) r, curid, id);
			goto failed;
		} else if ( ! p->lib_list[id].loaded &&
				IS_ERR_VALUE(load_flat_shared_library(id, p))) {
			printk("BINFMT_FLAT: failed to load library %d", id);
			goto failed;
		}
		/* Check versioning information (i.e. time stamps) */
		if (p->lib_list[id].build_date && p->lib_list[curid].build_date &&
				p->lib_list[curid].build_date < p->lib_list[id].build_date) {
			printk("BINFMT_FLAT: library %d is younger than %d", id, curid);
			goto failed;
		}
	}
#else
	id = 0;
#endif

	start_brk = p->lib_list[id].start_brk;
	start_data = p->lib_list[id].start_data;
	start_code = p->lib_list[id].start_code;
	text_len = p->lib_list[id].text_len;

	if (!flat_reloc_valid(r, start_brk - start_data + text_len)) {
		printk("BINFMT_FLAT: reloc outside program 0x%x (0 - 0x%x/0x%x)",
		       (int) r,(int)(start_brk-start_code),(int)text_len);
		goto failed;
	}

	if (r < text_len)			/* In text segment */
		addr = r + start_code;
	else					/* In data segment */
		addr = r - text_len + start_data;

	/* Range checked already above so doing the range tests is redundant...*/
	return(addr);

failed:
	printk(", killing %s!\n", current->comm);
	send_sig(SIGSEGV, current, 0);

	return RELOC_FAILED;
}