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
 scalar_t__ strchr (char*,char const) ; 

int utilfdt_decode_type(const char *fmt, int *type, int *size)
{
	int qualifier = 0;

	if (!*fmt)
		return -1;

	/* get the conversion qualifier */
	*size = -1;
	if (strchr("hlLb", *fmt)) {
		qualifier = *fmt++;
		if (qualifier == *fmt) {
			switch (*fmt++) {
/* TODO:		case 'l': qualifier = 'L'; break;*/
			case 'h':
				qualifier = 'b';
				break;
			}
		}
	}

	/* we should now have a type */
	if ((*fmt == '\0') || !strchr("iuxs", *fmt))
		return -1;

	/* convert qualifier (bhL) to byte size */
	if (*fmt != 's')
		*size = qualifier == 'b' ? 1 :
				qualifier == 'h' ? 2 :
				qualifier == 'l' ? 4 : -1;
	*type = *fmt++;

	/* that should be it! */
	if (*fmt)
		return -1;
	return 0;
}