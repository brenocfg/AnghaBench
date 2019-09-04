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
struct dso {TYPE_2__* funcdescs; scalar_t__ got; TYPE_1__* syms; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {scalar_t__ got; scalar_t__ addr; } ;
struct TYPE_4__ {int st_info; int /*<<< orphan*/  st_value; scalar_t__ st_shndx; } ;

/* Variables and functions */
 int STT_FUNC ; 
 int /*<<< orphan*/  a_crash () ; 
 size_t count_syms (struct dso*) ; 
 TYPE_2__* dl_mmap (size_t) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ laddr (struct dso*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 
 TYPE_2__* malloc (size_t) ; 
 int /*<<< orphan*/ * rtld_fail ; 
 int /*<<< orphan*/  runtime ; 

__attribute__((used)) static void makefuncdescs(struct dso *p)
{
	static int self_done;
	size_t nsym = count_syms(p);
	size_t i, size = nsym * sizeof(*p->funcdescs);

	if (!self_done) {
		p->funcdescs = dl_mmap(size);
		self_done = 1;
	} else {
		p->funcdescs = malloc(size);
	}
	if (!p->funcdescs) {
		if (!runtime) a_crash();
		error("Error allocating function descriptors for %s", p->name);
		longjmp(*rtld_fail, 1);
	}
	for (i=0; i<nsym; i++) {
		if ((p->syms[i].st_info&0xf)==STT_FUNC && p->syms[i].st_shndx) {
			p->funcdescs[i].addr = laddr(p, p->syms[i].st_value);
			p->funcdescs[i].got = p->got;
		} else {
			p->funcdescs[i].addr = 0;
			p->funcdescs[i].got = 0;
		}
	}
}