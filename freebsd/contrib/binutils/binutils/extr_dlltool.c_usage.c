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
 char* mname ; 
 char* program_name ; 

__attribute__((used)) static void
usage (FILE *file, int status)
{
  /* xgetext:c-format */
  fprintf (file, _("Usage %s <option(s)> <object-file(s)>\n"), program_name);
  /* xgetext:c-format */
  fprintf (file, _("   -m --machine <machine>    Create as DLL for <machine>.  [default: %s]\n"), mname);
  fprintf (file, _("        possible <machine>: arm[_interwork], i386, mcore[-elf]{-le|-be}, ppc, thumb\n"));
  fprintf (file, _("   -e --output-exp <outname> Generate an export file.\n"));
  fprintf (file, _("   -l --output-lib <outname> Generate an interface library.\n"));
  fprintf (file, _("   -a --add-indirect         Add dll indirects to export file.\n"));
  fprintf (file, _("   -D --dllname <name>       Name of input dll to put into interface lib.\n"));
  fprintf (file, _("   -d --input-def <deffile>  Name of .def file to be read in.\n"));
  fprintf (file, _("   -z --output-def <deffile> Name of .def file to be created.\n"));
  fprintf (file, _("      --export-all-symbols   Export all symbols to .def\n"));
  fprintf (file, _("      --no-export-all-symbols  Only export listed symbols\n"));
  fprintf (file, _("      --exclude-symbols <list> Don't export <list>\n"));
  fprintf (file, _("      --no-default-excludes  Clear default exclude symbols\n"));
  fprintf (file, _("   -b --base-file <basefile> Read linker generated base file.\n"));
  fprintf (file, _("   -x --no-idata4            Don't generate idata$4 section.\n"));
  fprintf (file, _("   -c --no-idata5            Don't generate idata$5 section.\n"));
  fprintf (file, _("   -U --add-underscore       Add underscores to all symbols in interface library.\n"));
  fprintf (file, _("      --add-stdcall-underscore Add underscores to stdcall symbols in interface library.\n"));
  fprintf (file, _("   -k --kill-at              Kill @<n> from exported names.\n"));
  fprintf (file, _("   -A --add-stdcall-alias    Add aliases without @<n>.\n"));
  fprintf (file, _("   -p --ext-prefix-alias <prefix> Add aliases with <prefix>.\n"));
  fprintf (file, _("   -S --as <name>            Use <name> for assembler.\n"));
  fprintf (file, _("   -f --as-flags <flags>     Pass <flags> to the assembler.\n"));
  fprintf (file, _("   -C --compat-implib        Create backward compatible import library.\n"));
  fprintf (file, _("   -n --no-delete            Keep temp files (repeat for extra preservation).\n"));
  fprintf (file, _("   -t --temp-prefix <prefix> Use <prefix> to construct temp file names.\n"));
  fprintf (file, _("   -v --verbose              Be verbose.\n"));
  fprintf (file, _("   -V --version              Display the program version.\n"));
  fprintf (file, _("   -h --help                 Display this information.\n"));
  fprintf (file, _("   @<file>                   Read options from <file>.\n"));
#ifdef DLLTOOL_MCORE_ELF
  fprintf (file, _("   -M --mcore-elf <outname>  Process mcore-elf object files into <outname>.\n"));
  fprintf (file, _("   -L --linker <name>        Use <name> as the linker.\n"));
  fprintf (file, _("   -F --linker-flags <flags> Pass <flags> to the linker.\n"));
#endif
  if (REPORT_BUGS_TO[0] && status == 0)
    fprintf (file, _("Report bugs to %s\n"), REPORT_BUGS_TO);
  exit (status);
}