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

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * safe_abs_relocs ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static int is_safe_abs_reloc(const char* sym_name)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(safe_abs_relocs); i++) {
		if (!strcmp(sym_name, safe_abs_relocs[i]))
			/* Match found */
			return 1;
	}
	if (strncmp(sym_name, "VDSO", 4) == 0)
		return 1;
	if (strncmp(sym_name, "__crc_", 6) == 0)
		return 1;
	return 0;
}