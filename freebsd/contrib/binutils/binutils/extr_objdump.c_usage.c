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
 int /*<<< orphan*/  disassembler_usage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  list_supported_architectures (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_supported_targets (char*,int /*<<< orphan*/ *) ; 
 char* program_name ; 

__attribute__((used)) static void
usage (FILE *stream, int status)
{
  fprintf (stream, _("Usage: %s <option(s)> <file(s)>\n"), program_name);
  fprintf (stream, _(" Display information from object <file(s)>.\n"));
  fprintf (stream, _(" At least one of the following switches must be given:\n"));
  fprintf (stream, _("\
  -a, --archive-headers    Display archive header information\n\
  -f, --file-headers       Display the contents of the overall file header\n\
  -p, --private-headers    Display object format specific file header contents\n\
  -h, --[section-]headers  Display the contents of the section headers\n\
  -x, --all-headers        Display the contents of all headers\n\
  -d, --disassemble        Display assembler contents of executable sections\n\
  -D, --disassemble-all    Display assembler contents of all sections\n\
  -S, --source             Intermix source code with disassembly\n\
  -s, --full-contents      Display the full contents of all sections requested\n\
  -g, --debugging          Display debug information in object file\n\
  -e, --debugging-tags     Display debug information using ctags style\n\
  -G, --stabs              Display (in raw form) any STABS info in the file\n\
  -W, --dwarf              Display DWARF info in the file\n\
  -t, --syms               Display the contents of the symbol table(s)\n\
  -T, --dynamic-syms       Display the contents of the dynamic symbol table\n\
  -r, --reloc              Display the relocation entries in the file\n\
  -R, --dynamic-reloc      Display the dynamic relocation entries in the file\n\
  @<file>                  Read options from <file>\n\
  -v, --version            Display this program's version number\n\
  -i, --info               List object formats and architectures supported\n\
  -H, --help               Display this information\n\
"));
  if (status != 2)
    {
      fprintf (stream, _("\n The following switches are optional:\n"));
      fprintf (stream, _("\
  -b, --target=BFDNAME           Specify the target object format as BFDNAME\n\
  -m, --architecture=MACHINE     Specify the target architecture as MACHINE\n\
  -j, --section=NAME             Only display information for section NAME\n\
  -M, --disassembler-options=OPT Pass text OPT on to the disassembler\n\
  -EB --endian=big               Assume big endian format when disassembling\n\
  -EL --endian=little            Assume little endian format when disassembling\n\
      --file-start-context       Include context from start of file (with -S)\n\
  -I, --include=DIR              Add DIR to search list for source files\n\
  -l, --line-numbers             Include line numbers and filenames in output\n\
  -C, --demangle[=STYLE]         Decode mangled/processed symbol names\n\
                                  The STYLE, if specified, can be `auto', `gnu',\n\
                                  `lucid', `arm', `hp', `edg', `gnu-v3', `java'\n\
                                  or `gnat'\n\
  -w, --wide                     Format output for more than 80 columns\n\
  -z, --disassemble-zeroes       Do not skip blocks of zeroes when disassembling\n\
      --start-address=ADDR       Only process data whose address is >= ADDR\n\
      --stop-address=ADDR        Only process data whose address is <= ADDR\n\
      --prefix-addresses         Print complete address alongside disassembly\n\
      --[no-]show-raw-insn       Display hex alongside symbolic disassembly\n\
      --adjust-vma=OFFSET        Add OFFSET to all displayed section addresses\n\
      --special-syms             Include special symbols in symbol dumps\n\
\n"));
      list_supported_targets (program_name, stream);
      list_supported_architectures (program_name, stream);

      disassembler_usage (stream);
    }
  if (REPORT_BUGS_TO[0] && status == 0)
    fprintf (stream, _("Report bugs to %s.\n"), REPORT_BUGS_TO);
  exit (status);
}