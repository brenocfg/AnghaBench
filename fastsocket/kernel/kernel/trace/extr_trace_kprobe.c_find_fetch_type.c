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
struct fetch_type {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct fetch_type const*) ; 
 char* DEFAULT_FETCH_TYPE_STR ; 
 struct fetch_type const* fetch_type_table ; 
 char* strchr (char const*,char) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strict_strtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static const struct fetch_type *find_fetch_type(const char *type)
{
	int i;

	if (!type)
		type = DEFAULT_FETCH_TYPE_STR;

	/* Special case: bitfield */
	if (*type == 'b') {
		unsigned long bs;
		type = strchr(type, '/');
		if (!type)
			goto fail;
		type++;
		if (strict_strtoul(type, 0, &bs))
			goto fail;
		switch (bs) {
		case 8:
			return find_fetch_type("u8");
		case 16:
			return find_fetch_type("u16");
		case 32:
			return find_fetch_type("u32");
		case 64:
			return find_fetch_type("u64");
		default:
			goto fail;
		}
	}

	for (i = 0; i < ARRAY_SIZE(fetch_type_table); i++)
		if (strcmp(type, fetch_type_table[i].name) == 0)
			return &fetch_type_table[i];
fail:
	return NULL;
}