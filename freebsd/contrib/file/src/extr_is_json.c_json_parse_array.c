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
 int /*<<< orphan*/  DPRINTF (char*,unsigned char const*,unsigned char const*) ; 
 size_t JSON_ARRAYN ; 
 int /*<<< orphan*/  json_parse (unsigned char const**,unsigned char const*,size_t*,size_t) ; 

__attribute__((used)) static int
json_parse_array(const unsigned char **ucp, const unsigned char *ue,
	size_t *st, size_t lvl)
{
	const unsigned char *uc = *ucp;
	int more = 0;	/* Array has more than 1 element */

	DPRINTF("Parse array: ", uc, *ucp);
	while (uc < ue) {
		if (!json_parse(&uc, ue, st, lvl + 1))
			goto out;
		if (uc == ue)
			goto out;
		switch (*uc) {
		case ',':
			more++;
			uc++;
			continue;
		case ']':
			if (more)
				st[JSON_ARRAYN]++;
			*ucp = uc + 1;
			return 1;
		default:
			goto out;
		}
	}
out:
	DPRINTF("Bad array: ", uc,  *ucp);
	*ucp = uc;
	return 0;
}