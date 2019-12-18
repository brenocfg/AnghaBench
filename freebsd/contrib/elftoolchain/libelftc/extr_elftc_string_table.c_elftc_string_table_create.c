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
struct _Elftc_String_Table_Bucket {int dummy; } ;
struct _Elftc_String_Table {char* st_string_pool; int st_nbuckets; size_t st_string_pool_size; scalar_t__ st_len; int /*<<< orphan*/ * st_buckets; } ;
typedef  struct _Elftc_String_Table Elftc_String_Table ;

/* Variables and functions */
 size_t ELFTC_STRING_TABLE_DEFAULT_SIZE ; 
 size_t ELFTC_STRING_TABLE_EXPECTED_CHAIN_LENGTH ; 
 size_t ELFTC_STRING_TABLE_EXPECTED_STRING_SIZE ; 
 int /*<<< orphan*/  ELFTC_STRING_TABLE_UPDATE_LENGTH (struct _Elftc_String_Table*,int) ; 
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct _Elftc_String_Table*) ; 
 void* malloc (size_t) ; 

Elftc_String_Table *
elftc_string_table_create(size_t sizehint)
{
	struct _Elftc_String_Table *st;
	int n, nbuckets, tablesize;

	if (sizehint < ELFTC_STRING_TABLE_DEFAULT_SIZE)
		sizehint = ELFTC_STRING_TABLE_DEFAULT_SIZE;

	nbuckets = sizehint / (ELFTC_STRING_TABLE_EXPECTED_CHAIN_LENGTH *
	    ELFTC_STRING_TABLE_EXPECTED_STRING_SIZE);

	tablesize = sizeof(struct _Elftc_String_Table) +
	    nbuckets * sizeof(struct _Elftc_String_Table_Bucket);

	if ((st = malloc(tablesize)) == NULL)
		return (NULL);
	if ((st->st_string_pool = malloc(sizehint)) == NULL) {
		free(st);
		return (NULL);
	}

	for (n = 0; n < nbuckets; n++)
		SLIST_INIT(&st->st_buckets[n]);

	st->st_len = 0;
	st->st_nbuckets = nbuckets;
	st->st_string_pool_size = sizehint;
	*st->st_string_pool = '\0';
	ELFTC_STRING_TABLE_UPDATE_LENGTH(st, 1);

	return (st);
}