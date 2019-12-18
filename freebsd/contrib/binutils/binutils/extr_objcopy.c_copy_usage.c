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
 int /*<<< orphan*/  list_supported_targets (char*,int /*<<< orphan*/ *) ; 
 char* program_name ; 

__attribute__((used)) static void
copy_usage (FILE *stream, int exit_status)
{
  fprintf (stream, _("Usage: %s [option(s)] in-file [out-file]\n"), program_name);
  fprintf (stream, _(" Copies a binary file, possibly transforming it in the process\n"));
  fprintf (stream, _(" The options are:\n"));
  fprintf (stream, _("\
  -I --input-target <bfdname>      Assume input file is in format <bfdname>\n\
  -O --output-target <bfdname>     Create an output file in format <bfdname>\n\
  -B --binary-architecture <arch>  Set arch of output file, when input is binary\n\
  -F --target <bfdname>            Set both input and output format to <bfdname>\n\
     --debugging                   Convert debugging information, if possible\n\
  -p --preserve-dates              Copy modified/access timestamps to the output\n\
  -j --only-section <name>         Only copy section <name> into the output\n\
     --add-gnu-debuglink=<file>    Add section .gnu_debuglink linking to <file>\n\
  -R --remove-section <name>       Remove section <name> from the output\n\
  -S --strip-all                   Remove all symbol and relocation information\n\
  -g --strip-debug                 Remove all debugging symbols & sections\n\
     --strip-unneeded              Remove all symbols not needed by relocations\n\
  -N --strip-symbol <name>         Do not copy symbol <name>\n\
     --strip-unneeded-symbol <name>\n\
                                   Do not copy symbol <name> unless needed by\n\
                                     relocations\n\
     --only-keep-debug             Strip everything but the debug information\n\
     --extract-symbol              Remove section contents but keep symbols\n\
  -K --keep-symbol <name>          Do not strip symbol <name>\n\
     --keep-file-symbols           Do not strip file symbol(s)\n\
     --localize-hidden             Turn all ELF hidden symbols into locals\n\
  -L --localize-symbol <name>      Force symbol <name> to be marked as a local\n\
     --globalize-symbol <name>     Force symbol <name> to be marked as a global\n\
  -G --keep-global-symbol <name>   Localize all symbols except <name>\n\
  -W --weaken-symbol <name>        Force symbol <name> to be marked as a weak\n\
     --weaken                      Force all global symbols to be marked as weak\n\
  -w --wildcard                    Permit wildcard in symbol comparison\n\
  -x --discard-all                 Remove all non-global symbols\n\
  -X --discard-locals              Remove any compiler-generated symbols\n\
  -i --interleave <number>         Only copy one out of every <number> bytes\n\
  -b --byte <num>                  Select byte <num> in every interleaved block\n\
     --gap-fill <val>              Fill gaps between sections with <val>\n\
     --pad-to <addr>               Pad the last section up to address <addr>\n\
     --set-start <addr>            Set the start address to <addr>\n\
    {--change-start|--adjust-start} <incr>\n\
                                   Add <incr> to the start address\n\
    {--change-addresses|--adjust-vma} <incr>\n\
                                   Add <incr> to LMA, VMA and start addresses\n\
    {--change-section-address|--adjust-section-vma} <name>{=|+|-}<val>\n\
                                   Change LMA and VMA of section <name> by <val>\n\
     --change-section-lma <name>{=|+|-}<val>\n\
                                   Change the LMA of section <name> by <val>\n\
     --change-section-vma <name>{=|+|-}<val>\n\
                                   Change the VMA of section <name> by <val>\n\
    {--[no-]change-warnings|--[no-]adjust-warnings}\n\
                                   Warn if a named section does not exist\n\
     --set-section-flags <name>=<flags>\n\
                                   Set section <name>'s properties to <flags>\n\
     --add-section <name>=<file>   Add section <name> found in <file> to output\n\
     --rename-section <old>=<new>[,<flags>] Rename section <old> to <new>\n\
     --change-leading-char         Force output format's leading character style\n\
     --remove-leading-char         Remove leading character from global symbols\n\
     --reverse-bytes=<num>         Reverse <num> bytes at a time, in output sections with content\n\
     --redefine-sym <old>=<new>    Redefine symbol name <old> to <new>\n\
     --redefine-syms <file>        --redefine-sym for all symbol pairs \n\
                                     listed in <file>\n\
     --srec-len <number>           Restrict the length of generated Srecords\n\
     --srec-forceS3                Restrict the type of generated Srecords to S3\n\
     --strip-symbols <file>        -N for all symbols listed in <file>\n\
     --strip-unneeded-symbols <file>\n\
                                   --strip-unneeded-symbol for all symbols listed\n\
                                     in <file>\n\
     --keep-symbols <file>         -K for all symbols listed in <file>\n\
     --localize-symbols <file>     -L for all symbols listed in <file>\n\
     --globalize-symbols <file>    --globalize-symbol for all in <file>\n\
     --keep-global-symbols <file>  -G for all symbols listed in <file>\n\
     --weaken-symbols <file>       -W for all symbols listed in <file>\n\
     --alt-machine-code <index>    Use the target's <index>'th alternative machine\n\
     --writable-text               Mark the output text as writable\n\
     --readonly-text               Make the output text write protected\n\
     --pure                        Mark the output file as demand paged\n\
     --impure                      Mark the output file as impure\n\
     --prefix-symbols <prefix>     Add <prefix> to start of every symbol name\n\
     --prefix-sections <prefix>    Add <prefix> to start of every section name\n\
     --prefix-alloc-sections <prefix>\n\
                                   Add <prefix> to start of every allocatable\n\
                                     section name\n\
  -v --verbose                     List all object files modified\n\
  @<file>                          Read options from <file>\n\
  -V --version                     Display this program's version number\n\
  -h --help                        Display this output\n\
     --info                        List object formats & architectures supported\n\
"));
  list_supported_targets (program_name, stream);
  if (REPORT_BUGS_TO[0] && exit_status == 0)
    fprintf (stream, _("Report bugs to %s\n"), REPORT_BUGS_TO);
  exit (exit_status);
}