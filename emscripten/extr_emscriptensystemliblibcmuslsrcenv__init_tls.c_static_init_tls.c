#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pthread {int dummy; } ;
struct TYPE_6__ {int tls_cnt; int tls_align; int tls_size; TYPE_2__* tls_head; } ;
struct TYPE_5__ {uintptr_t size; int align; uintptr_t offset; void* image; int /*<<< orphan*/  len; } ;
struct TYPE_4__ {scalar_t__ p_type; size_t p_vaddr; uintptr_t p_memsz; int p_align; int /*<<< orphan*/  p_filesz; } ;
typedef  TYPE_1__ Phdr ;

/* Variables and functions */
 size_t AT_PHDR ; 
 size_t AT_PHENT ; 
 size_t AT_PHNUM ; 
 int MAP_ANONYMOUS ; 
 int MAP_PRIVATE ; 
 int MIN_TLS_ALIGN ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 scalar_t__ PT_PHDR ; 
 scalar_t__ PT_TLS ; 
 int /*<<< orphan*/  SYS_mmap ; 
 int /*<<< orphan*/  __copy_tls (void*) ; 
 scalar_t__ __init_tp (int /*<<< orphan*/ ) ; 
 scalar_t__ __syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a_crash () ; 
 void* builtin_tls ; 
 TYPE_3__ libc ; 
 TYPE_2__ main_tls ; 

__attribute__((used)) static void static_init_tls(size_t *aux)
{
	unsigned char *p;
	size_t n;
	Phdr *phdr, *tls_phdr=0;
	size_t base = 0;
	void *mem;

	for (p=(void *)aux[AT_PHDR],n=aux[AT_PHNUM]; n; n--,p+=aux[AT_PHENT]) {
		phdr = (void *)p;
		if (phdr->p_type == PT_PHDR)
			base = aux[AT_PHDR] - phdr->p_vaddr;
		if (phdr->p_type == PT_TLS)
			tls_phdr = phdr;
	}

	if (tls_phdr) {
		main_tls.image = (void *)(base + tls_phdr->p_vaddr);
		main_tls.len = tls_phdr->p_filesz;
		main_tls.size = tls_phdr->p_memsz;
		main_tls.align = tls_phdr->p_align;
		libc.tls_cnt = 1;
		libc.tls_head = &main_tls;
	}

	main_tls.size += (-main_tls.size - (uintptr_t)main_tls.image)
		& (main_tls.align-1);
	if (main_tls.align < MIN_TLS_ALIGN) main_tls.align = MIN_TLS_ALIGN;
#ifndef TLS_ABOVE_TP
	main_tls.offset = main_tls.size;
#endif

	libc.tls_align = main_tls.align;
	libc.tls_size = 2*sizeof(void *) + sizeof(struct pthread)
		+ main_tls.size + main_tls.align
		+ MIN_TLS_ALIGN-1 & -MIN_TLS_ALIGN;

	if (libc.tls_size > sizeof builtin_tls) {
#ifndef SYS_mmap2
#define SYS_mmap2 SYS_mmap
#endif
		mem = (void *)__syscall(
			SYS_mmap2,
			0, libc.tls_size, PROT_READ|PROT_WRITE,
			MAP_ANONYMOUS|MAP_PRIVATE, -1, 0);
		/* -4095...-1 cast to void * will crash on dereference anyway,
		 * so don't bloat the init code checking for error codes and
		 * explicitly calling a_crash(). */
	} else {
		mem = builtin_tls;
	}

	/* Failure to initialize thread pointer is always fatal. */
	if (__init_tp(__copy_tls(mem)) < 0)
		a_crash();
}