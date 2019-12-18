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
 int /*<<< orphan*/  json_parse (unsigned char const**,unsigned char const*,size_t*,size_t) ; 
 int /*<<< orphan*/  json_parse_string (unsigned char const**,unsigned char const*) ; 
 unsigned char* json_skip_space (unsigned char const*,unsigned char const*) ; 

__attribute__((used)) static int
json_parse_object(const unsigned char **ucp, const unsigned char *ue,
	size_t *st, size_t lvl)
{
	const unsigned char *uc = *ucp;
	DPRINTF("Parse object: ", uc, *ucp);
	while (uc < ue) {
		uc = json_skip_space(uc, ue);
		if (uc == ue)
			goto out;
		if (*uc++ != '"') {
			DPRINTF("not string", uc, *ucp);
			goto out;
		}
		DPRINTF("next field", uc, *ucp);
		if (!json_parse_string(&uc, ue)) {
			DPRINTF("not string", uc, *ucp);
			goto out;
		}
		uc = json_skip_space(uc, ue);
		if (uc == ue)
			goto out;
		if (*uc++ != ':') {
			DPRINTF("not colon", uc, *ucp);
			goto out;
		}
		if (!json_parse(&uc, ue, st, lvl + 1)) {
			DPRINTF("not json", uc, *ucp);
			goto out;
		}
		if (uc == ue)
			goto out;
		switch (*uc++) {
		case ',':
			continue;
		case '}': /* { */
			*ucp = uc;
			DPRINTF("Good object: ", uc, *ucp);
			return 1;
		default:
			*ucp = uc - 1;
			DPRINTF("not more", uc, *ucp);
			goto out;
		}
	}
out:
	DPRINTF("Bad object: ", uc, *ucp);
	*ucp = uc;
	return 0;
}