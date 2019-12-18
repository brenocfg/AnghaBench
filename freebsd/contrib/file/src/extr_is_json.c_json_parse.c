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
 int JSON_ARRAY ; 
 size_t JSON_ARRAYN ; 
 int JSON_CONSTANT ; 
 int JSON_NUMBER ; 
 size_t JSON_OBJECT ; 
 int JSON_STRING ; 
 int json_parse_array (unsigned char const**,unsigned char const*,size_t*,size_t) ; 
 int json_parse_const (unsigned char const**,unsigned char const*,char*,int) ; 
 int json_parse_number (unsigned char const**,unsigned char const*) ; 
 int json_parse_object (unsigned char const**,unsigned char const*,size_t*,size_t) ; 
 int json_parse_string (unsigned char const**,unsigned char const*) ; 
 unsigned char* json_skip_space (unsigned char const*,unsigned char const*) ; 

__attribute__((used)) static int
json_parse(const unsigned char **ucp, const unsigned char *ue,
    size_t *st, size_t lvl)
{
	const unsigned char *uc;
	int rv = 0;
	int t;

	uc = json_skip_space(*ucp, ue);
	if (uc == ue)
		goto out;

	// Avoid recursion
	if (lvl > 20)
		return 0;
#if JSON_COUNT
	/* bail quickly if not counting */
	if (lvl > 1 && (st[JSON_OBJECT] || st[JSON_ARRAYN]))
		return 1;
#endif

	DPRINTF("Parse general: ", uc, *ucp);
	switch (*uc++) {
	case '"':
		rv = json_parse_string(&uc, ue);
		t = JSON_STRING;
		break;
	case '[':
		rv = json_parse_array(&uc, ue, st, lvl + 1);
		t = JSON_ARRAY;
		break;
	case '{': /* '}' */
		rv = json_parse_object(&uc, ue, st, lvl + 1);
		t = JSON_OBJECT;
		break;
	case 't':
		rv = json_parse_const(&uc, ue, "true", sizeof("true"));
		t = JSON_CONSTANT;
		break;
	case 'f':
		rv = json_parse_const(&uc, ue, "false", sizeof("false"));
		t = JSON_CONSTANT;
		break;
	case 'n':
		rv = json_parse_const(&uc, ue, "null", sizeof("null"));
		t = JSON_CONSTANT;
		break;
	default:
		--uc;
		rv = json_parse_number(&uc, ue);
		t = JSON_NUMBER;
		break;
	}
	if (rv)
		st[t]++;
	uc = json_skip_space(uc, ue);
out:
	*ucp = uc;
	DPRINTF("End general: ", uc, *ucp);
	if (lvl == 0)
		return rv && (st[JSON_ARRAYN] || st[JSON_OBJECT]);
	return rv;
}