#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char const* ar_name; } ;
struct TYPE_8__ {scalar_t__ e_shnum; scalar_t__ e_type; } ;
typedef  int /*<<< orphan*/  GElf_Shdr ;
typedef  TYPE_1__ GElf_Ehdr ;
typedef  int /*<<< orphan*/  Elf_Scn ;
typedef  int /*<<< orphan*/  Elf_Cmd ;
typedef  TYPE_2__ Elf_Arhdr ;
typedef  int /*<<< orphan*/  Elf ;

/* Variables and functions */
 int /*<<< orphan*/  ELF_C_READ ; 
 scalar_t__ ELF_K_ELF ; 
 scalar_t__ ELF_K_NONE ; 
 scalar_t__ ET_CORE ; 
 int RETURN_DATAERR ; 
 int RETURN_OK ; 
 scalar_t__ STYLE_BERKELEY ; 
 int /*<<< orphan*/  berkeley_calc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  berkeley_footer (char const*,char const*,char*) ; 
 int /*<<< orphan*/  berkeley_header () ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/ * elf_begin (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_end (int /*<<< orphan*/ *) ; 
 TYPE_2__* elf_getarhdr (int /*<<< orphan*/ *) ; 
 scalar_t__ elf_kind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * elf_nextscn (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gelf_getehdr (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * gelf_getshdr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int handle_core (char const*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ style ; 
 int /*<<< orphan*/  sysv_calc (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysv_footer () ; 
 int /*<<< orphan*/  sysv_header (char const*,TYPE_2__*) ; 
 int /*<<< orphan*/  warnx (char*,char const*) ; 

__attribute__((used)) static int
handle_elf(int fd, const char *name)
{
	GElf_Ehdr elfhdr;
	GElf_Shdr shdr;
	Elf *elf, *elf1;
	Elf_Arhdr *arhdr;
	Elf_Scn *scn;
	Elf_Cmd elf_cmd;
	int exit_code;

	elf_cmd = ELF_C_READ;
	elf1 = elf_begin(fd, elf_cmd, NULL);
	while ((elf = elf_begin(fd, elf_cmd, elf1)) != NULL) {
		arhdr = elf_getarhdr(elf);
		if (elf_kind(elf) == ELF_K_NONE && arhdr == NULL) {
			(void) elf_end(elf);
			(void) elf_end(elf1);
			(void) close(fd);
			return (RETURN_DATAERR);
		}
		if (elf_kind(elf) != ELF_K_ELF ||
		    (gelf_getehdr(elf, &elfhdr) == NULL)) {
			elf_cmd = elf_next(elf);
			(void) elf_end(elf);
			warnx("%s: File format not recognized",
			    arhdr != NULL ? arhdr->ar_name : name);
			continue;
		}
		/* Core dumps are handled separately */
		if (elfhdr.e_shnum == 0 && elfhdr.e_type == ET_CORE) {
			exit_code = handle_core(name, elf, &elfhdr);
			(void) elf_end(elf);
			(void) elf_end(elf1);
			(void) close(fd);
			return (exit_code);
		} else {
			scn = NULL;
			if (style == STYLE_BERKELEY) {
				berkeley_header();
				while ((scn = elf_nextscn(elf, scn)) != NULL) {
					if (gelf_getshdr(scn, &shdr) != NULL)
						berkeley_calc(&shdr);
				}
			} else {
				sysv_header(name, arhdr);
				scn = NULL;
				while ((scn = elf_nextscn(elf, scn)) != NULL) {
					if (gelf_getshdr(scn, &shdr) !=	NULL)
						sysv_calc(elf, &elfhdr, &shdr);
				}
			}
			if (style == STYLE_BERKELEY) {
				if (arhdr != NULL) {
					berkeley_footer(name, arhdr->ar_name,
					    "ex");
				} else {
					berkeley_footer(name, NULL, "ex");
				}
			} else {
				sysv_footer();
			}
		}
		elf_cmd = elf_next(elf);
		(void) elf_end(elf);
	}
	(void) elf_end(elf1);
	(void) close(fd);
	return (RETURN_OK);
}