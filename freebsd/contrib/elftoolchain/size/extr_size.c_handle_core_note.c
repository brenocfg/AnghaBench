#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int pid_t ;
typedef  int int32_t ;
struct TYPE_15__ {int n_type; int n_descsz; int n_namesz; } ;
struct TYPE_14__ {int /*<<< orphan*/ * e_ident; } ;
struct TYPE_13__ {size_t p_offset; size_t p_filesz; } ;
typedef  TYPE_1__ GElf_Phdr ;
typedef  size_t GElf_Off ;
typedef  TYPE_2__ GElf_Ehdr ;
typedef  int /*<<< orphan*/  Elf32_Word ;
typedef  TYPE_3__ Elf32_Nhdr ;
typedef  int /*<<< orphan*/  Elf ;

/* Variables and functions */
 int BUF_SIZE ; 
 size_t EI_CLASS ; 
 size_t EI_OSABI ; 
 int /*<<< orphan*/  ELFCLASS32 ; 
 int /*<<< orphan*/  ELFOSABI_FREEBSD ; 
 size_t ELF_ALIGN (int,int) ; 
 int /*<<< orphan*/  ELF_T_WORD ; 
 int /*<<< orphan*/  NEXT_NOTE (TYPE_2__*,int,int,size_t) ; 
 scalar_t__ NOTE_OFFSET_32 (TYPE_3__*,int,int) ; 
 scalar_t__ NOTE_OFFSET_64 (TYPE_3__*,int,int) ; 
#define  NT_AUXV 135 
#define  NT_FPREGSET 134 
#define  NT_LWPSTATUS 133 
#define  NT_PRPSINFO 132 
#define  NT_PRSTATUS 131 
#define  NT_PRXFPREG 130 
#define  NT_PSINFO 129 
#define  NT_PSTATUS 128 
 int PID32 (TYPE_3__*,int,int) ; 
 int PID64 (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  STYLE_SYSV ; 
 char* elf_rawfile (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  radix ; 
 int regxfp_pseudo ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strdup (scalar_t__) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  style ; 
 int /*<<< orphan*/  tbl_append () ; 
 int /*<<< orphan*/  tbl_print (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tbl_print_num (int,int /*<<< orphan*/ ,int) ; 
 int text_size_total ; 
 int /*<<< orphan*/  warnx (char*) ; 
 int /*<<< orphan*/  xlatetom (int /*<<< orphan*/ *,TYPE_2__*,int*,int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
handle_core_note(Elf *elf, GElf_Ehdr *elfhdr, GElf_Phdr *phdr,
    char **cmd_line)
{
	size_t max_size, segment_end;
	uint64_t raw_size;
	GElf_Off offset;
	static pid_t pid;
	uintptr_t ver;
	Elf32_Nhdr *nhdr, nhdr_l;
	static int reg_pseudo = 0, reg2_pseudo = 0 /*, regxfp_pseudo = 0*/;
	char buf[BUF_SIZE], *data, *name;

 	if (elf == NULL || elfhdr == NULL || phdr == NULL)
		return;

	data = elf_rawfile(elf, &max_size);
	offset = phdr->p_offset;
	if (offset >= max_size || phdr->p_filesz > max_size - offset) {
		warnx("invalid PHDR offset");
		return;
	}
	segment_end = phdr->p_offset + phdr->p_filesz;

	while (data != NULL && offset + sizeof(Elf32_Nhdr) < segment_end) {
		nhdr = (Elf32_Nhdr *)(uintptr_t)((char*)data + offset);
		memset(&nhdr_l, 0, sizeof(Elf32_Nhdr));
		if (!xlatetom(elf, elfhdr, &nhdr->n_type, &nhdr_l.n_type,
			ELF_T_WORD, sizeof(Elf32_Word)) ||
		    !xlatetom(elf, elfhdr, &nhdr->n_descsz, &nhdr_l.n_descsz,
			ELF_T_WORD, sizeof(Elf32_Word)) ||
		    !xlatetom(elf, elfhdr, &nhdr->n_namesz, &nhdr_l.n_namesz,
			ELF_T_WORD, sizeof(Elf32_Word)))
			break;

		if (offset + sizeof(Elf32_Nhdr) +
		    ELF_ALIGN(nhdr_l.n_namesz, 4) +
		    ELF_ALIGN(nhdr_l.n_descsz, 4) >= segment_end) {
			warnx("invalid note header");
			return;
		}

		name = (char *)((char *)nhdr + sizeof(Elf32_Nhdr));
		switch (nhdr_l.n_type) {
		case NT_PRSTATUS: {
			raw_size = 0;
			if (elfhdr->e_ident[EI_OSABI] == ELFOSABI_FREEBSD &&
			    nhdr_l.n_namesz == 0x8 &&
			    !strcmp(name,"FreeBSD")) {
				if (elfhdr->e_ident[EI_CLASS] == ELFCLASS32) {
					raw_size = (uint64_t)*((uint32_t *)
					    (uintptr_t)(name +
						ELF_ALIGN((int32_t)
						nhdr_l.n_namesz, 4) + 8));
					ver = (uintptr_t)NOTE_OFFSET_32(nhdr,
					    nhdr_l.n_namesz,0);
					if (*((int *)ver) == 1)
						pid = PID32(nhdr,
						    nhdr_l.n_namesz, 24);
				} else {
					raw_size = *((uint64_t *)(uintptr_t)
					    (name + ELF_ALIGN((int32_t)
						nhdr_l.n_namesz, 8) + 16));
					ver = (uintptr_t)NOTE_OFFSET_64(nhdr,
					    nhdr_l.n_namesz,0);
					if (*((int *)ver) == 1)
						pid = PID64(nhdr,
						    nhdr_l.n_namesz, 40);
				}
				xlatetom(elf, elfhdr, &raw_size, &raw_size,
				    ELF_T_WORD, sizeof(uint64_t));
				xlatetom(elf, elfhdr, &pid, &pid, ELF_T_WORD,
				    sizeof(pid_t));
			}

			if (raw_size != 0 && style == STYLE_SYSV) {
				(void) snprintf(buf, BUF_SIZE, "%s/%d",
				    ".reg", pid);
				tbl_append();
				tbl_print(buf, 0);
				tbl_print_num(raw_size, radix, 1);
				tbl_print_num(0, radix, 2);
				if (!reg_pseudo) {
					tbl_append();
					tbl_print(".reg", 0);
					tbl_print_num(raw_size, radix, 1);
					tbl_print_num(0, radix, 2);
					reg_pseudo = 1;
					text_size_total += raw_size;
				}
				text_size_total += raw_size;
			}
		}
		break;
		case NT_FPREGSET:	/* same as NT_PRFPREG */
			if (style == STYLE_SYSV) {
				(void) snprintf(buf, BUF_SIZE,
				    "%s/%d", ".reg2", pid);
				tbl_append();
				tbl_print(buf, 0);
				tbl_print_num(nhdr_l.n_descsz, radix, 1);
				tbl_print_num(0, radix, 2);
				if (!reg2_pseudo) {
					tbl_append();
					tbl_print(".reg2", 0);
					tbl_print_num(nhdr_l.n_descsz, radix,
					    1);
					tbl_print_num(0, radix, 2);
					reg2_pseudo = 1;
					text_size_total += nhdr_l.n_descsz;
				}
				text_size_total += nhdr_l.n_descsz;
			}
			break;
#if 0
		case NT_AUXV:
			if (style == STYLE_SYSV) {
				tbl_append();
				tbl_print(".auxv", 0);
				tbl_print_num(nhdr_l.n_descsz, radix, 1);
				tbl_print_num(0, radix, 2);
				text_size_total += nhdr_l.n_descsz;
			}
			break;
		case NT_PRXFPREG:
			if (style == STYLE_SYSV) {
				(void) snprintf(buf, BUF_SIZE, "%s/%d",
				    ".reg-xfp", pid);
				tbl_append();
				tbl_print(buf, 0);
				tbl_print_num(nhdr_l.n_descsz, radix, 1);
				tbl_print_num(0, radix, 2);
				if (!regxfp_pseudo) {
					tbl_append();
					tbl_print(".reg-xfp", 0);
					tbl_print_num(nhdr_l.n_descsz, radix,
					    1);
					tbl_print_num(0, radix, 2);
					regxfp_pseudo = 1;
					text_size_total += nhdr_l.n_descsz;
				}
				text_size_total += nhdr_l.n_descsz;
			}
			break;
		case NT_PSINFO:
#endif
		case NT_PRPSINFO: {
			/* FreeBSD 64-bit */
			if (nhdr_l.n_descsz == 0x78 &&
				!strcmp(name,"FreeBSD")) {
				*cmd_line = strdup(NOTE_OFFSET_64(nhdr,
				    nhdr_l.n_namesz, 33));
			/* FreeBSD 32-bit */
			} else if (nhdr_l.n_descsz == 0x6c &&
				!strcmp(name,"FreeBSD")) {
				*cmd_line = strdup(NOTE_OFFSET_32(nhdr,
				    nhdr_l.n_namesz, 25));
			}
			/* Strip any trailing spaces */
			if (*cmd_line != NULL) {
				char *s;

				s = *cmd_line + strlen(*cmd_line);
				while (s > *cmd_line) {
					if (*(s-1) != 0x20) break;
					s--;
				}
				*s = 0;
			}
			break;
		}
#if 0
		case NT_PSTATUS:
		case NT_LWPSTATUS:
#endif
		default:
			break;
		}
		NEXT_NOTE(elfhdr, nhdr_l.n_descsz, nhdr_l.n_namesz, offset);
	}
}