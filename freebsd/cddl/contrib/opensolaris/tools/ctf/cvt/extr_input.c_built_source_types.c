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
typedef  int /*<<< orphan*/  symit_data_t ;
typedef  int /*<<< orphan*/  source_types_t ;
typedef  int /*<<< orphan*/  Elf ;

/* Variables and functions */
 int /*<<< orphan*/  SOURCE_C ; 
 int /*<<< orphan*/  SOURCE_NONE ; 
 int /*<<< orphan*/  SOURCE_S ; 
 int /*<<< orphan*/  SOURCE_UNKNOWN ; 
 int /*<<< orphan*/  STT_FILE ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  symit_free (int /*<<< orphan*/ *) ; 
 char* symit_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * symit_new (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * symit_next (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

source_types_t
built_source_types(Elf *elf, char const *file)
{
	source_types_t types = SOURCE_NONE;
	symit_data_t *si;

	if ((si = symit_new(elf, file)) == NULL)
		return (SOURCE_NONE);

	while (symit_next(si, STT_FILE) != NULL) {
		char *name = symit_name(si);
		size_t len = strlen(name);
		if (len < 2 || name[len - 2] != '.') {
			types |= SOURCE_UNKNOWN;
			continue;
		}

		switch (name[len - 1]) {
		case 'c':
			types |= SOURCE_C;
			break;
		case 'h':
			/* ignore */
			break;
		case 's':
		case 'S':
			types |= SOURCE_S;
			break;
		default:
			types |= SOURCE_UNKNOWN;
		}
	}

	symit_free(si);
	return (types);
}