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
struct ia64_boot_param {int dummy; } ;
struct elfhdr {int* e_ident; scalar_t__ e_type; unsigned long e_entry; unsigned long e_phnum; unsigned long e_phoff; } ;
struct elf_phdr {scalar_t__ p_type; int p_filesz; unsigned long p_offset; scalar_t__ p_memsz; int /*<<< orphan*/  p_paddr; } ;
struct disk_stat {int fd; int count; } ;
struct disk_req {int len; long addr; } ;
typedef  int /*<<< orphan*/  mem ;

/* Variables and functions */
 scalar_t__ ET_EXEC ; 
 scalar_t__ PT_LOAD ; 
 int /*<<< orphan*/  SSC_CLOSE ; 
 int /*<<< orphan*/  SSC_CONSOLE_INIT ; 
 int /*<<< orphan*/  SSC_EXIT ; 
 int /*<<< orphan*/  SSC_GET_ARGS ; 
 int /*<<< orphan*/  SSC_LOAD_SYMBOLS ; 
 int /*<<< orphan*/  SSC_OPEN ; 
 int /*<<< orphan*/  SSC_READ ; 
 int /*<<< orphan*/  SSC_WAIT_COMPLETION ; 
 int /*<<< orphan*/  _IA64_REG_AR_KR0 ; 
 long __pa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cons_write (char*) ; 
 int /*<<< orphan*/  debug_break () ; 
 int /*<<< orphan*/  elf_check_arch (struct elfhdr*) ; 
 int /*<<< orphan*/  ia64_setreg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jmp_to_kernel (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 void* ssc (int,long,long,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int*,char*,int) ; 
 struct ia64_boot_param* sys_fw_init (char*,long) ; 

void
start_bootloader (void)
{
	static char mem[4096];
	static char buffer[1024];
	unsigned long off;
	int fd, i;
	struct disk_req req;
	struct disk_stat stat;
	struct elfhdr *elf;
	struct elf_phdr *elf_phdr;	/* program header */
	unsigned long e_entry, e_phoff, e_phnum;
	register struct ia64_boot_param *bp;
	char *kpath, *args;
	long arglen = 0;

	ssc(0, 0, 0, 0, SSC_CONSOLE_INIT);

	/*
	 * S.Eranian: extract the commandline argument from the simulator
	 *
	 * The expected format is as follows:
         *
	 *	kernelname args...
	 *
	 * Both are optional but you can't have the second one without the first.
	 */
	arglen = ssc((long) buffer, 0, 0, 0, SSC_GET_ARGS);

	kpath = "vmlinux";
	args = buffer;
	if (arglen > 0) {
		kpath = buffer;
		while (*args != ' ' && *args != '\0')
			++args, --arglen;
		if (*args == ' ')
			*args++ = '\0', --arglen;
	}

	if (arglen <= 0) {
		args = "";
		arglen = 1;
	}

	fd = ssc((long) kpath, 1, 0, 0, SSC_OPEN);

	if (fd < 0) {
		cons_write(kpath);
		cons_write(": file not found, reboot now\n");
		for(;;);
	}
	stat.fd = fd;
	off = 0;

	req.len = sizeof(mem);
	req.addr = (long) mem;
	ssc(fd, 1, (long) &req, off, SSC_READ);
	ssc((long) &stat, 0, 0, 0, SSC_WAIT_COMPLETION);

	elf = (struct elfhdr *) mem;
	if (elf->e_ident[0] == 0x7f && strncmp(elf->e_ident + 1, "ELF", 3) != 0) {
		cons_write("not an ELF file\n");
		return;
	}
	if (elf->e_type != ET_EXEC) {
		cons_write("not an ELF executable\n");
		return;
	}
	if (!elf_check_arch(elf)) {
		cons_write("kernel not for this processor\n");
		return;
	}

	e_entry = elf->e_entry;
	e_phnum = elf->e_phnum;
	e_phoff = elf->e_phoff;

	cons_write("loading ");
	cons_write(kpath);
	cons_write("...\n");

	for (i = 0; i < e_phnum; ++i) {
		req.len = sizeof(*elf_phdr);
		req.addr = (long) mem;
		ssc(fd, 1, (long) &req, e_phoff, SSC_READ);
		ssc((long) &stat, 0, 0, 0, SSC_WAIT_COMPLETION);
		if (stat.count != sizeof(*elf_phdr)) {
			cons_write("failed to read phdr\n");
			return;
		}
		e_phoff += sizeof(*elf_phdr);

		elf_phdr = (struct elf_phdr *) mem;

		if (elf_phdr->p_type != PT_LOAD)
			continue;

		req.len = elf_phdr->p_filesz;
		req.addr = __pa(elf_phdr->p_paddr);
		ssc(fd, 1, (long) &req, elf_phdr->p_offset, SSC_READ);
		ssc((long) &stat, 0, 0, 0, SSC_WAIT_COMPLETION);
		memset((char *)__pa(elf_phdr->p_paddr) + elf_phdr->p_filesz, 0,
		       elf_phdr->p_memsz - elf_phdr->p_filesz);
	}
	ssc(fd, 0, 0, 0, SSC_CLOSE);

	cons_write("starting kernel...\n");

	/* fake an I/O base address: */
	ia64_setreg(_IA64_REG_AR_KR0, 0xffffc000000UL);

	bp = sys_fw_init(args, arglen);

	ssc(0, (long) kpath, 0, 0, SSC_LOAD_SYMBOLS);

	debug_break();
	jmp_to_kernel((unsigned long) bp, e_entry);

	cons_write("kernel returned!\n");
	ssc(-1, 0, 0, 0, SSC_EXIT);
}