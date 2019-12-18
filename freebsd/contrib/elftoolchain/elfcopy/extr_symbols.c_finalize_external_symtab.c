#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct symbuf {size_t ngs; TYPE_4__* g64; TYPE_3__* g32; } ;
struct TYPE_10__ {scalar_t__ sz; } ;
struct strbuf {TYPE_5__ l; } ;
struct elfcopy {scalar_t__ oec; TYPE_2__* strtab; TYPE_1__* symtab; } ;
struct TYPE_9__ {scalar_t__ st_name; } ;
struct TYPE_8__ {scalar_t__ st_name; } ;
struct TYPE_7__ {struct strbuf* buf; } ;
struct TYPE_6__ {struct symbuf* buf; } ;
typedef  scalar_t__ Elf64_Word ;
typedef  scalar_t__ Elf32_Word ;

/* Variables and functions */
 scalar_t__ ELFCLASS32 ; 

void
finalize_external_symtab(struct elfcopy *ecp)
{
	struct symbuf *sy_buf;
	struct strbuf *st_buf;
	int i;

	/*
	 * Update st_name for global/weak symbols. (global/weak symbols
	 * are put after local symbols)
	 */
	sy_buf = ecp->symtab->buf;
	st_buf = ecp->strtab->buf;
	for (i = 0; (size_t) i < sy_buf->ngs; i++) {
		if (ecp->oec == ELFCLASS32) {
			if (sy_buf->g32[i].st_name == (Elf32_Word)-1)
				sy_buf->g32[i].st_name = 0;
			else
				sy_buf->g32[i].st_name += st_buf->l.sz;
		} else {
			if (sy_buf->g64[i].st_name == (Elf64_Word)-1)
				sy_buf->g64[i].st_name = 0;
			else
				sy_buf->g64[i].st_name += st_buf->l.sz;
		}
	}
}