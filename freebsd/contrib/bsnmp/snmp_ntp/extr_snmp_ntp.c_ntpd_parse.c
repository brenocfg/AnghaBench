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
typedef  char u_char ;

/* Variables and functions */
 scalar_t__ isspace (int) ; 

__attribute__((used)) static int
ntpd_parse(u_char **data, size_t *datalen, char **namep, char **valp)
{
	u_char *ptr = *data;
	u_char *end = ptr + *datalen;
	char *ptr1;
	char endc;

	/* skip leading spaces */
	while (ptr < end && isspace((int)*ptr))
		ptr++;

	if (ptr == end)
		return (0);

	*namep = ptr;

	/* skip to space or '=' or ','*/
	while (ptr < end && !isspace((int)*ptr) && *ptr != '=' && *ptr != ',')
		ptr++;
	endc = *ptr;
	*ptr++ = '\0';

	/* skip space */
	while (ptr < end && isspace((int)*ptr))
		ptr++;

	if (ptr == end || endc == ',') {
		/* no value */
		*valp = NULL;
		*datalen -= ptr - *data;
		*data = ptr;
		return (1);
	}

	if (*ptr == '"') {
		/* quoted */
		ptr++;
		*valp = ptr;
		while (ptr < end && *ptr != '"')
			ptr++;
		if (ptr == end)
			return (0);

		*ptr++ = '\0';

		/* find comma */
		while (ptr < end && isspace((int)*ptr) && *ptr == ',')
			ptr++;
	} else {
		*valp = ptr;

		/* skip to end of value */
		while (ptr < end && *ptr != ',')
			ptr++;

		/* remove trailing blanks */
		for (ptr1 = ptr; ptr1 > *valp; ptr1--)
			if (!isspace((int)ptr1[-1]))
				break;
		*ptr1 = '\0';

		if (ptr < end)
			ptr++;
	}

	*datalen -= ptr - *data;
	*data = ptr;

	return (1);
}