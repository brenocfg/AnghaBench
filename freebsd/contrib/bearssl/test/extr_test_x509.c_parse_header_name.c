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
 char* SB_contents (int /*<<< orphan*/ ) ; 
 size_t SB_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_name_char (char) ; 
 scalar_t__ is_ws (char) ; 
 int /*<<< orphan*/  line_builder ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 char* xmalloc (size_t) ; 

__attribute__((used)) static char *
parse_header_name(void)
{
	char *buf, *name;
	size_t u, v, w, len;

	buf = SB_contents(line_builder);
	len = SB_length(line_builder);
	if (len < 2 || buf[0] != '[' || buf[len - 1] != ']') {
		return NULL;
	}
	u = 1;
	v = len - 1;
	while (u < v && is_ws(buf[u])) {
		u ++;
	}
	while (u < v && is_ws(buf[v - 1])) {
		v --;
	}
	if (u == v) {
		return NULL;
	}
	for (w = u; w < v; w ++) {
		if (!is_name_char(buf[w])) {
			return NULL;
		}
	}
	len = v - u;
	name = xmalloc(len + 1);
	memcpy(name, buf + u, len);
	name[len] = 0;
	return name;
}