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
typedef  enum gen_funcs { ____Placeholder_gen_funcs } gen_funcs ;

/* Variables and functions */
 int GEN_FUNCS_C ; 
 int GEN_FUNCS_H ; 
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 int /*<<< orphan*/  extract_all_enums (int /*<<< orphan*/ ,int) ; 
 scalar_t__ extract_enum (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gen_all_enum_funcs (int /*<<< orphan*/ ,int) ; 
 scalar_t__ gen_enum_funcs_str (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
make_enums(int argc, char *argv[], enum gen_funcs gen_funcs)
{
	if (gen_funcs == GEN_FUNCS_C) {
		if (argc == 0)
			gen_all_enum_funcs(stdout, 1);
		else {
			for (int i = 0; i < argc; i++)
				if (gen_enum_funcs_str(stdout, argv[i]))
					errx(1, "enum not found: %s", argv[i]);
		}
	} else {
		if (argc == 0)
			extract_all_enums(stdout, gen_funcs == GEN_FUNCS_H);
		else {
			for (int i = 0; i < argc; i++)
				if (extract_enum(stdout, argv[i],
				    gen_funcs == GEN_FUNCS_H))
					errx(1, "enum not found: %s", argv[i]);
		}
	}
}