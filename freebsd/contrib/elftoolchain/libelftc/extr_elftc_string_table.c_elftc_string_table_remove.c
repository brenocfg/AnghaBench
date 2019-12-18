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
struct _Elftc_String_Table_Entry {scalar_t__ ste_idx; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  Elftc_String_Table ;

/* Variables and functions */
 int ELFTC_FAILURE ; 
 size_t ELFTC_STRING_TABLE_LENGTH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ELFTC_STRING_TABLE_SET_COMPACTION_FLAG (int /*<<< orphan*/ *) ; 
 int ELFTC_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 struct _Elftc_String_Table_Entry* elftc_string_table_find_hash_entry (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

int
elftc_string_table_remove(Elftc_String_Table *st, const char *string)
{
	struct _Elftc_String_Table_Entry *ste;
	ssize_t idx;

	ste = elftc_string_table_find_hash_entry(st, string, NULL);

	if (ste == NULL || (idx = ste->ste_idx) < 0)
		return (ELFTC_FAILURE);

	assert(idx > 0 && (size_t)idx < ELFTC_STRING_TABLE_LENGTH(st));

	ste->ste_idx = -idx;

	ELFTC_STRING_TABLE_SET_COMPACTION_FLAG(st);

	return (ELFTC_SUCCESS);
}