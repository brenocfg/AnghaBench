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
 int /*<<< orphan*/  PERF_COLOR_RESET ; 
 int /*<<< orphan*/  die (char*,int,char const*,char const*) ; 
 scalar_t__ isspace (char const) ; 
 int parse_attr (char const*,int) ; 
 int parse_color (char const*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncasecmp (char const*,char*,int) ; 

void color_parse_mem(const char *value, int value_len, const char *var,
		char *dst)
{
	const char *ptr = value;
	int len = value_len;
	int attr = -1;
	int fg = -2;
	int bg = -2;

	if (!strncasecmp(value, "reset", len)) {
		strcpy(dst, PERF_COLOR_RESET);
		return;
	}

	/* [fg [bg]] [attr] */
	while (len > 0) {
		const char *word = ptr;
		int val, wordlen = 0;

		while (len > 0 && !isspace(word[wordlen])) {
			wordlen++;
			len--;
		}

		ptr = word + wordlen;
		while (len > 0 && isspace(*ptr)) {
			ptr++;
			len--;
		}

		val = parse_color(word, wordlen);
		if (val >= -1) {
			if (fg == -2) {
				fg = val;
				continue;
			}
			if (bg == -2) {
				bg = val;
				continue;
			}
			goto bad;
		}
		val = parse_attr(word, wordlen);
		if (val < 0 || attr != -1)
			goto bad;
		attr = val;
	}

	if (attr >= 0 || fg >= 0 || bg >= 0) {
		int sep = 0;

		*dst++ = '\033';
		*dst++ = '[';
		if (attr >= 0) {
			*dst++ = '0' + attr;
			sep++;
		}
		if (fg >= 0) {
			if (sep++)
				*dst++ = ';';
			if (fg < 8) {
				*dst++ = '3';
				*dst++ = '0' + fg;
			} else {
				dst += sprintf(dst, "38;5;%d", fg);
			}
		}
		if (bg >= 0) {
			if (sep++)
				*dst++ = ';';
			if (bg < 8) {
				*dst++ = '4';
				*dst++ = '0' + bg;
			} else {
				dst += sprintf(dst, "48;5;%d", bg);
			}
		}
		*dst++ = 'm';
	}
	*dst = 0;
	return;
bad:
	die("bad color value '%.*s' for variable '%s'", value_len, value, var);
}