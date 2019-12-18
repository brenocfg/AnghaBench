#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ulong_t ;
typedef  int ssize_t ;
struct TYPE_6__ {size_t str_hashsz; TYPE_2__** str_hash; } ;
typedef  TYPE_1__ dt_strtab_t ;
struct TYPE_7__ {int str_off; struct TYPE_7__* str_next; } ;
typedef  TYPE_2__ dt_strhash_t ;

/* Variables and functions */
 scalar_t__ dt_strtab_compare (TYPE_1__*,TYPE_2__*,char const*,size_t) ; 
 size_t dt_strtab_hash (char const*,size_t*) ; 

ssize_t
dt_strtab_index(dt_strtab_t *sp, const char *str)
{
	dt_strhash_t *hp;
	size_t len;
	ulong_t h;

	if (str == NULL || str[0] == '\0')
		return (0); /* we keep a \0 at offset 0 to simplify things */

	h = dt_strtab_hash(str, &len) % sp->str_hashsz;

	for (hp = sp->str_hash[h]; hp != NULL; hp = hp->str_next) {
		if (dt_strtab_compare(sp, hp, str, len + 1) == 0)
			return (hp->str_off);
	}

	return (-1);
}