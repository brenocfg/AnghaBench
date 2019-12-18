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
 int /*<<< orphan*/ * strchr (char const*,char) ; 
 int strlen (char const*) ; 

__attribute__((used)) static char *escape(const char* text, char *bf, int len)
{
	char *bfp = bf;
	int multiline = strchr(text, '\n') != NULL;
	int eol = 0;
	int textlen = strlen(text);

	if ((textlen > 0) && (text[textlen-1] == '\n'))
		eol = 1;

	*bfp++ = '"';
	--len;

	if (multiline) {
		*bfp++ = '"';
		*bfp++ = '\n';
		*bfp++ = '"';
		len -= 3;
	}

	while (*text != '\0' && len > 1) {
		if (*text == '"')
			*bfp++ = '\\';
		else if (*text == '\n') {
			*bfp++ = '\\';
			*bfp++ = 'n';
			*bfp++ = '"';
			*bfp++ = '\n';
			*bfp++ = '"';
			len -= 5;
			++text;
			goto next;
		}
		else if (*text == '\\') {
			*bfp++ = '\\';
			len--;
		}
		*bfp++ = *text++;
next:
		--len;
	}

	if (multiline && eol)
		bfp -= 3;

	*bfp++ = '"';
	*bfp = '\0';

	return bf;
}