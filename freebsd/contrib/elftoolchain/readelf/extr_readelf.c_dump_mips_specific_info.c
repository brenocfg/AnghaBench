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
struct section {scalar_t__ type; int /*<<< orphan*/ * name; } ;
struct readelf {size_t shnum; struct section* sl; } ;

/* Variables and functions */
 scalar_t__ SHT_MIPS_ABIFLAGS ; 
 scalar_t__ SHT_MIPS_OPTIONS ; 
 scalar_t__ SHT_MIPS_REGINFO ; 
 int /*<<< orphan*/  dump_mips_abiflags (struct readelf*,struct section*) ; 
 int /*<<< orphan*/  dump_mips_options (struct readelf*,struct section*) ; 
 int /*<<< orphan*/  dump_mips_reginfo (struct readelf*,struct section*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
dump_mips_specific_info(struct readelf *re)
{
	struct section *s;
	int i;

	s = NULL;
	for (i = 0; (size_t) i < re->shnum; i++) {
		s = &re->sl[i];
		if (s->name != NULL && (!strcmp(s->name, ".MIPS.options") ||
		    (s->type == SHT_MIPS_OPTIONS))) {
			dump_mips_options(re, s);
		}
	}

	if (s->name != NULL && (!strcmp(s->name, ".MIPS.abiflags") ||
	    (s->type == SHT_MIPS_ABIFLAGS)))
		dump_mips_abiflags(re, s);

	/*
	 * Dump .reginfo if present (although it will be ignored by an OS if a
	 * .MIPS.options section is present, according to SGI mips64 spec).
	 */
	for (i = 0; (size_t) i < re->shnum; i++) {
		s = &re->sl[i];
		if (s->name != NULL && (!strcmp(s->name, ".reginfo") ||
		    (s->type == SHT_MIPS_REGINFO)))
			dump_mips_reginfo(re, s);
	}
}