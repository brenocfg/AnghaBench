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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* REPORT_BUGS_TO ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/ * stdout ; 

__attribute__((used)) static void
usage (FILE *stream)
{
  fprintf (stream, _("Usage: readelf <option(s)> elf-file(s)\n"));
  fprintf (stream, _(" Display information about the contents of ELF format files\n"));
  fprintf (stream, _(" Options are:\n\
  -a --all               Equivalent to: -h -l -S -s -r -d -V -A -I\n\
  -h --file-header       Display the ELF file header\n\
  -l --program-headers   Display the program headers\n\
     --segments          An alias for --program-headers\n\
  -S --section-headers   Display the sections' header\n\
     --sections          An alias for --section-headers\n\
  -g --section-groups    Display the section groups\n\
  -t --section-details   Display the section details\n\
  -e --headers           Equivalent to: -h -l -S\n\
  -s --syms              Display the symbol table\n\
      --symbols          An alias for --syms\n\
  -n --notes             Display the core notes (if present)\n\
  -r --relocs            Display the relocations (if present)\n\
  -u --unwind            Display the unwind info (if present)\n\
  -d --dynamic           Display the dynamic section (if present)\n\
  -V --version-info      Display the version sections (if present)\n\
  -A --arch-specific     Display architecture specific information (if any).\n\
  -D --use-dynamic       Use the dynamic section info when displaying symbols\n\
  -x --hex-dump=<number> Dump the contents of section <number>\n\
  -w[liaprmfFsoR] or\n\
  --debug-dump[=line,=info,=abbrev,=pubnames,=aranges,=macro,=frames,=str,=loc,=Ranges]\n\
                         Display the contents of DWARF2 debug sections\n"));
#ifdef SUPPORT_DISASSEMBLY
  fprintf (stream, _("\
  -i --instruction-dump=<number>\n\
                         Disassemble the contents of section <number>\n"));
#endif
  fprintf (stream, _("\
  -I --histogram         Display histogram of bucket list lengths\n\
  -W --wide              Allow output width to exceed 80 characters\n\
  @<file>                Read options from <file>\n\
  -H --help              Display this information\n\
  -v --version           Display the version number of readelf\n"));
  
  if (REPORT_BUGS_TO[0] && stream == stdout)
    fprintf (stdout, _("Report bugs to %s\n"), REPORT_BUGS_TO);

  exit (stream == stdout ? 0 : 1);
}