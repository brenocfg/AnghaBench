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
typedef  int wchar_t ;
typedef  int /*<<< orphan*/  mbstate_t ;
typedef  int /*<<< orphan*/  mbr ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FPRINTF (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  MB_CUR_MAX ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 size_t mbrtowc (int*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nvlist_print_json_string(FILE *fp, const char *input)
{
	mbstate_t mbr;
	wchar_t c;
	size_t sz;

	bzero(&mbr, sizeof (mbr));

	FPRINTF(fp, "\"");
	while ((sz = mbrtowc(&c, input, MB_CUR_MAX, &mbr)) > 0) {
		switch (c) {
		case '"':
			FPRINTF(fp, "\\\"");
			break;
		case '\n':
			FPRINTF(fp, "\\n");
			break;
		case '\r':
			FPRINTF(fp, "\\r");
			break;
		case '\\':
			FPRINTF(fp, "\\\\");
			break;
		case '\f':
			FPRINTF(fp, "\\f");
			break;
		case '\t':
			FPRINTF(fp, "\\t");
			break;
		case '\b':
			FPRINTF(fp, "\\b");
			break;
		default:
			if ((c >= 0x00 && c <= 0x1f) ||
			    (c > 0x7f && c <= 0xffff)) {
				/*
				 * Render both Control Characters and Unicode
				 * characters in the Basic Multilingual Plane
				 * as JSON-escaped multibyte characters.
				 */
				FPRINTF(fp, "\\u%04x", (int)(0xffff & c));
			} else if (c >= 0x20 && c <= 0x7f) {
				/*
				 * Render other 7-bit ASCII characters directly
				 * and drop other, unrepresentable characters.
				 */
				FPRINTF(fp, "%c", (int)(0xff & c));
			}
			break;
		}
		input += sz;
	}

	if (sz == (size_t)-1 || sz == (size_t)-2) {
		/*
		 * We last read an invalid multibyte character sequence,
		 * so return an error.
		 */
		return (-1);
	}

	FPRINTF(fp, "\"");
	return (0);
}