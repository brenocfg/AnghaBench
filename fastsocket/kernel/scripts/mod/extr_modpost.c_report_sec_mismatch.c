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
typedef  enum mismatch { ____Placeholder_mismatch } mismatch ;

/* Variables and functions */
#define  DATA_TO_EXIT 137 
#define  DATA_TO_INIT 136 
#define  EXIT_TO_INIT 135 
#define  EXPORT_TO_INIT_EXIT 134 
#define  INIT_TO_EXIT 133 
#define  NO_MISMATCH 132 
#define  TEXT_TO_EXIT 131 
#define  TEXT_TO_INIT 130 
#define  XXXEXIT_TO_EXIT 129 
#define  XXXINIT_TO_INIT 128 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* sec2annotation (char const*) ; 
 int /*<<< orphan*/  sec_mismatch_count ; 
 int /*<<< orphan*/  sec_mismatch_verbose ; 
 int /*<<< orphan*/  stderr ; 
 char** symbol_white_list ; 
 int /*<<< orphan*/  warn (char*,char const*,char const*,unsigned long long,char const*,char const*,char const*,char const*,char const*,char const*,char const*) ; 

__attribute__((used)) static void report_sec_mismatch(const char *modname, enum mismatch mismatch,
                                const char *fromsec,
                                unsigned long long fromaddr,
                                const char *fromsym,
                                int from_is_func,
                                const char *tosec, const char *tosym,
                                int to_is_func)
{
	const char *from, *from_p;
	const char *to, *to_p;

	switch (from_is_func) {
	case 0: from = "variable"; from_p = "";   break;
	case 1: from = "function"; from_p = "()"; break;
	default: from = "(unknown reference)"; from_p = ""; break;
	}
	switch (to_is_func) {
	case 0: to = "variable"; to_p = "";   break;
	case 1: to = "function"; to_p = "()"; break;
	default: to = "(unknown reference)"; to_p = ""; break;
	}

	sec_mismatch_count++;
	if (!sec_mismatch_verbose)
		return;

	warn("%s(%s+0x%llx): Section mismatch in reference from the %s %s%s "
	     "to the %s %s:%s%s\n",
	     modname, fromsec, fromaddr, from, fromsym, from_p, to, tosec,
	     tosym, to_p);

	switch (mismatch) {
	case TEXT_TO_INIT:
		fprintf(stderr,
		"The function %s%s() references\n"
		"the %s %s%s%s.\n"
		"This is often because %s lacks a %s\n"
		"annotation or the annotation of %s is wrong.\n",
		sec2annotation(fromsec), fromsym,
		to, sec2annotation(tosec), tosym, to_p,
		fromsym, sec2annotation(tosec), tosym);
		break;
	case DATA_TO_INIT: {
		const char **s = symbol_white_list;
		fprintf(stderr,
		"The variable %s references\n"
		"the %s %s%s%s\n"
		"If the reference is valid then annotate the\n"
		"variable with __init* or __refdata (see linux/init.h) "
		"or name the variable:\n",
		fromsym, to, sec2annotation(tosec), tosym, to_p);
		while (*s)
			fprintf(stderr, "%s, ", *s++);
		fprintf(stderr, "\n");
		break;
	}
	case TEXT_TO_EXIT:
		fprintf(stderr,
		"The function %s() references a %s in an exit section.\n"
		"Often the %s %s%s has valid usage outside the exit section\n"
		"and the fix is to remove the %sannotation of %s.\n",
		fromsym, to, to, tosym, to_p, sec2annotation(tosec), tosym);
		break;
	case DATA_TO_EXIT: {
		const char **s = symbol_white_list;
		fprintf(stderr,
		"The variable %s references\n"
		"the %s %s%s%s\n"
		"If the reference is valid then annotate the\n"
		"variable with __exit* (see linux/init.h) or "
		"name the variable:\n",
		fromsym, to, sec2annotation(tosec), tosym, to_p);
		while (*s)
			fprintf(stderr, "%s, ", *s++);
		fprintf(stderr, "\n");
		break;
	}
	case XXXINIT_TO_INIT:
	case XXXEXIT_TO_EXIT:
		fprintf(stderr,
		"The %s %s%s%s references\n"
		"a %s %s%s%s.\n"
		"If %s is only used by %s then\n"
		"annotate %s with a matching annotation.\n",
		from, sec2annotation(fromsec), fromsym, from_p,
		to, sec2annotation(tosec), tosym, to_p,
		tosym, fromsym, tosym);
		break;
	case INIT_TO_EXIT:
		fprintf(stderr,
		"The %s %s%s%s references\n"
		"a %s %s%s%s.\n"
		"This is often seen when error handling "
		"in the init function\n"
		"uses functionality in the exit path.\n"
		"The fix is often to remove the %sannotation of\n"
		"%s%s so it may be used outside an exit section.\n",
		from, sec2annotation(fromsec), fromsym, from_p,
		to, sec2annotation(tosec), tosym, to_p,
		sec2annotation(tosec), tosym, to_p);
		break;
	case EXIT_TO_INIT:
		fprintf(stderr,
		"The %s %s%s%s references\n"
		"a %s %s%s%s.\n"
		"This is often seen when error handling "
		"in the exit function\n"
		"uses functionality in the init path.\n"
		"The fix is often to remove the %sannotation of\n"
		"%s%s so it may be used outside an init section.\n",
		from, sec2annotation(fromsec), fromsym, from_p,
		to, sec2annotation(tosec), tosym, to_p,
		sec2annotation(tosec), tosym, to_p);
		break;
	case EXPORT_TO_INIT_EXIT:
		fprintf(stderr,
		"The symbol %s is exported and annotated %s\n"
		"Fix this by removing the %sannotation of %s "
		"or drop the export.\n",
		tosym, sec2annotation(tosec), sec2annotation(tosec), tosym);
	case NO_MISMATCH:
		/* To get warnings on missing members */
		break;
	}
	fprintf(stderr, "\n");
}