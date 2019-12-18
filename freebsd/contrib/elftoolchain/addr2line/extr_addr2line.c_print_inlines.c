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
typedef  int /*<<< orphan*/  uintmax_t ;
struct Func {char* name; int call_file; int call_line; struct Func* inlined_caller; } ;
struct CU {scalar_t__ nsrcfiles; char** srcfiles; } ;
typedef  int /*<<< orphan*/  demangled ;
typedef  int Dwarf_Unsigned ;
typedef  scalar_t__ Dwarf_Signed ;

/* Variables and functions */
 scalar_t__ base ; 
 char* basename (char*) ; 
 scalar_t__ demangle ; 
 int /*<<< orphan*/  elftc_demangle (char*,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ func ; 
 scalar_t__ pretty_print ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* unknown ; 

__attribute__((used)) static void
print_inlines(struct CU *cu, struct Func *f, Dwarf_Unsigned call_file,
    Dwarf_Unsigned call_line)
{
	char demangled[1024];
	char *file;

	if (call_file > 0 && (Dwarf_Signed) call_file <= cu->nsrcfiles)
		file = cu->srcfiles[call_file - 1];
	else
		file = unknown;

	if (pretty_print)
		printf(" (inlined by) ");

	if (func) {
		if (demangle && !elftc_demangle(f->name, demangled,
		    sizeof(demangled), 0)) {
			if (pretty_print)
				printf("%s at ", demangled);
			else
				printf("%s\n", demangled);
		} else {
			if (pretty_print)
				printf("%s at ", f->name);
			else
				printf("%s\n", f->name);
		}
	}
	(void) printf("%s:%ju\n", base ? basename(file) : file,
	    (uintmax_t) call_line);

	if (f->inlined_caller != NULL)
		print_inlines(cu, f->inlined_caller, f->call_file,
		    f->call_line);
}