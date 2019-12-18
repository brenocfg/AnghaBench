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
typedef  scalar_t__ UWORD ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int Util_sscanhex (char const*) ; 
 int find_label_value (char const*) ; 
 int /*<<< orphan*/  printf (char*,char const*,int,int) ; 

__attribute__((used)) static int parse_hex(const char *s, UWORD *hexval)
{
	int x = Util_sscanhex(s);
#ifdef MONITOR_HINTS
	int y = find_label_value(s);
	if (y >= 0) {
		if (x < 0 || x > 0xffff || x == y) {
			*hexval = (UWORD) y;
			return TRUE;
		}
		/* s can be a hex number or a label name */
		printf("%s is ambiguous. Use 0%X or %X instead.\n", s, x, y);
		return FALSE;
	}
#endif
	if (x < 0 || x > 0xffff)
		return FALSE;
	*hexval = (UWORD) x;
	return TRUE;
}