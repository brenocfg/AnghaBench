#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  loc; } ;

/* Variables and functions */
 TYPE_1__* fcu_fans ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fan_check_loc_match(const char *loc, int fan)
{
	char	tmp[64];
	char	*c, *e;

	strlcpy(tmp, fcu_fans[fan].loc, 64);

	c = tmp;
	for (;;) {
		e = strchr(c, ',');
		if (e)
			*e = 0;
		if (strcmp(loc, c) == 0)
			return 1;
		if (e == NULL)
			break;
		c = e + 1;
	}
	return 0;
}