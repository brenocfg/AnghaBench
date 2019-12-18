#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* st_string_pool; } ;
typedef  TYPE_1__ Elftc_String_Table ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 size_t ELFTC_STRING_TABLE_LENGTH (TYPE_1__*) ; 
 int /*<<< orphan*/  errno ; 

const char *
elftc_string_table_to_string(Elftc_String_Table *st, size_t offset)
{
	const char *s;

	s = st->st_string_pool + offset;

	/*
	 * Check for:
	 * - An offset value within pool bounds.
	 * - A non-NUL byte at the specified offset.
	 * - The end of the prior string at offset - 1.
	 */
	if (offset == 0 || offset >= ELFTC_STRING_TABLE_LENGTH(st) ||
	    *s == '\0' || *(s - 1) != '\0') {
		errno = EINVAL;
		return (NULL);
	}

	return (s);
}