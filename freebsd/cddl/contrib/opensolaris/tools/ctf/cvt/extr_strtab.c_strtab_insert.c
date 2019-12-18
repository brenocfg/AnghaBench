#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ulong_t ;
struct TYPE_8__ {size_t str_hashsz; size_t str_size; int /*<<< orphan*/  str_nstrs; TYPE_2__** str_hash; scalar_t__ str_nbufs; int /*<<< orphan*/  str_ptr; } ;
typedef  TYPE_1__ strtab_t ;
struct TYPE_9__ {size_t str_off; size_t str_len; struct TYPE_9__* str_next; scalar_t__ str_buf; int /*<<< orphan*/  str_data; } ;
typedef  TYPE_2__ strhash_t ;

/* Variables and functions */
 scalar_t__ strtab_compare (TYPE_1__*,TYPE_2__*,char const*,size_t) ; 
 int /*<<< orphan*/  strtab_copyin (TYPE_1__*,char const*,size_t) ; 
 size_t strtab_hash (char const*,size_t*) ; 
 TYPE_2__* xmalloc (int) ; 

size_t
strtab_insert(strtab_t *sp, const char *str)
{
	strhash_t *hp;
	size_t len;
	ulong_t h;

	if (str == NULL || str[0] == '\0')
		return (0); /* we keep a \0 at offset 0 to simplify things */

	h = strtab_hash(str, &len) % sp->str_hashsz;

	/*
	 * If the string is already in our hash table, just return the offset
	 * of the existing string element and do not add a duplicate string.
	 */
	for (hp = sp->str_hash[h]; hp != NULL; hp = hp->str_next) {
		if (strtab_compare(sp, hp, str, len + 1) == 0)
			return (hp->str_off);
	}

	/*
	 * Create a new hash bucket, initialize it, and insert it at the front
	 * of the hash chain for the appropriate bucket.
	 */
	hp = xmalloc(sizeof (strhash_t));

	hp->str_data = sp->str_ptr;
	hp->str_buf = sp->str_nbufs - 1;
	hp->str_off = sp->str_size;
	hp->str_len = len;
	hp->str_next = sp->str_hash[h];

	sp->str_hash[h] = hp;

	/*
	 * Now copy the string data into our buffer list, and then update
	 * the global counts of strings and bytes.  Return str's byte offset.
	 */
	strtab_copyin(sp, str, len + 1);
	sp->str_nstrs++;
	sp->str_size += len + 1;

	return (hp->str_off);
}