#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_10__ {scalar_t__ e_shnum; scalar_t__ e_type; scalar_t__ e_phnum; } ;
struct TYPE_9__ {int p_type; } ;
typedef  TYPE_1__ GElf_Phdr ;
typedef  TYPE_2__ GElf_Ehdr ;
typedef  int /*<<< orphan*/  Elf ;

/* Variables and functions */
 scalar_t__ ET_CORE ; 
#define  PT_DYNAMIC 135 
#define  PT_GNU_EH_FRAME 134 
#define  PT_GNU_STACK 133 
#define  PT_INTERP 132 
#define  PT_LOAD 131 
 int PT_NOTE ; 
#define  PT_NULL 130 
#define  PT_PHDR 129 
#define  PT_SHLIB 128 
 int RETURN_DATAERR ; 
 int RETURN_OK ; 
 scalar_t__ STYLE_BERKELEY ; 
 scalar_t__ STYLE_SYSV ; 
 int /*<<< orphan*/  berkeley_footer (char*,char const*,char*) ; 
 int /*<<< orphan*/  berkeley_header () ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * gelf_getphdr (int /*<<< orphan*/ *,scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  handle_core_note (int /*<<< orphan*/ *,TYPE_2__*,TYPE_1__*,char**) ; 
 int /*<<< orphan*/  handle_phdr (int /*<<< orphan*/ *,TYPE_2__*,TYPE_1__*,scalar_t__,char const*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ style ; 
 int /*<<< orphan*/  sysv_footer () ; 
 int /*<<< orphan*/  sysv_header (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
handle_core(char const *name, Elf *elf, GElf_Ehdr *elfhdr)
{
	GElf_Phdr phdr;
	uint32_t i;
	char *core_cmdline;
	const char *seg_name;

	if (name == NULL || elf == NULL || elfhdr == NULL)
		return (RETURN_DATAERR);
	if  (elfhdr->e_shnum != 0 || elfhdr->e_type != ET_CORE)
		return (RETURN_DATAERR);

	seg_name = core_cmdline = NULL;
	if (style == STYLE_SYSV)
		sysv_header(name, NULL);
	else
		berkeley_header();

	for (i = 0; i < elfhdr->e_phnum; i++) {
		if (gelf_getphdr(elf, i, &phdr) != NULL) {
			if (phdr.p_type == PT_NOTE) {
				handle_phdr(elf, elfhdr, &phdr, i, "note");
				handle_core_note(elf, elfhdr, &phdr,
				    &core_cmdline);
			} else {
				switch(phdr.p_type) {
				case PT_NULL:
					seg_name = "null";
					break;
				case PT_LOAD:
					seg_name = "load";
					break;
				case PT_DYNAMIC:
					seg_name = "dynamic";
					break;
				case PT_INTERP:
					seg_name = "interp";
					break;
				case PT_SHLIB:
					seg_name = "shlib";
					break;
				case PT_PHDR:
					seg_name = "phdr";
					break;
				case PT_GNU_EH_FRAME:
					seg_name = "eh_frame_hdr";
					break;
				case PT_GNU_STACK:
					seg_name = "stack";
					break;
				default:
					seg_name = "segment";
				}
				handle_phdr(elf, elfhdr, &phdr, i, seg_name);
			}
		}
	}

	if (style == STYLE_BERKELEY) {
		if (core_cmdline != NULL) {
			berkeley_footer(core_cmdline, name,
			    "core file invoked as");
		} else {
			berkeley_footer(core_cmdline, name, "core file");
		}
	} else {
		sysv_footer();
		if (core_cmdline != NULL) {
			(void) printf(" (core file invoked as %s)\n\n",
			    core_cmdline);
		} else {
			(void) printf(" (core file)\n\n");
		}
	}
	free(core_cmdline);
	return (RETURN_OK);
}