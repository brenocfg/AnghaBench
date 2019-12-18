#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t st_string_pool_size; char* st_string_pool; } ;
typedef  TYPE_1__ Elftc_String_Table ;

/* Variables and functions */
 size_t ELFTC_STRING_TABLE_LENGTH (TYPE_1__*) ; 
 scalar_t__ ELFTC_STRING_TABLE_POOL_SIZE_INCREMENT ; 
 int /*<<< orphan*/  ELFTC_STRING_TABLE_UPDATE_LENGTH (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 char* realloc (char*,size_t) ; 
 size_t roundup (scalar_t__,scalar_t__) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int
elftc_string_table_add_to_pool(Elftc_String_Table *st, const char *string)
{
	char *newpool;
	size_t len, newsize, stlen;

	len = strlen(string) + 1; /* length, including the trailing NUL */
	stlen = ELFTC_STRING_TABLE_LENGTH(st);

	/* Resize the pool, if needed. */
	if (stlen + len >= st->st_string_pool_size) {
		newsize = roundup(st->st_string_pool_size +
		    ELFTC_STRING_TABLE_POOL_SIZE_INCREMENT,
		    ELFTC_STRING_TABLE_POOL_SIZE_INCREMENT);
		if ((newpool = realloc(st->st_string_pool, newsize)) ==
		    NULL)
			return (0);
		st->st_string_pool = newpool;
		st->st_string_pool_size = newsize;
	}

	memcpy(st->st_string_pool + stlen, string, len);
	ELFTC_STRING_TABLE_UPDATE_LENGTH(st, stlen + len);

	return (stlen);
}