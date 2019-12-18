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
typedef  unsigned char wchar_t ;

/* Variables and functions */
#define  CTLESC 128 
 int /*<<< orphan*/  collate_range_cmp (unsigned char,unsigned char) ; 
 unsigned char get_wc (char const**) ; 
 int /*<<< orphan*/  localeisutf8 ; 
 int match_charclass (char const*,unsigned char,char const**) ; 

__attribute__((used)) static int
patmatch(const char *pattern, const char *string)
{
	const char *p, *q, *end;
	const char *bt_p, *bt_q;
	char c;
	wchar_t wc, wc2;

	p = pattern;
	q = string;
	bt_p = NULL;
	bt_q = NULL;
	for (;;) {
		switch (c = *p++) {
		case '\0':
			if (*q != '\0')
				goto backtrack;
			return 1;
		case CTLESC:
			if (*q++ != *p++)
				goto backtrack;
			break;
		case '?':
			if (*q == '\0')
				return 0;
			if (localeisutf8) {
				wc = get_wc(&q);
				/*
				 * A '?' does not match invalid UTF-8 but a
				 * '*' does, so backtrack.
				 */
				if (wc == 0)
					goto backtrack;
			} else
				q++;
			break;
		case '*':
			c = *p;
			while (c == '*')
				c = *++p;
			/*
			 * If the pattern ends here, we know the string
			 * matches without needing to look at the rest of it.
			 */
			if (c == '\0')
				return 1;
			/*
			 * First try the shortest match for the '*' that
			 * could work. We can forget any earlier '*' since
			 * there is no way having it match more characters
			 * can help us, given that we are already here.
			 */
			bt_p = p;
			bt_q = q;
			break;
		case '[': {
			const char *savep, *saveq;
			int invert, found;
			wchar_t chr;

			savep = p, saveq = q;
			invert = 0;
			if (*p == '!' || *p == '^') {
				invert++;
				p++;
			}
			found = 0;
			if (*q == '\0')
				return 0;
			if (localeisutf8) {
				chr = get_wc(&q);
				if (chr == 0)
					goto backtrack;
			} else
				chr = (unsigned char)*q++;
			c = *p++;
			do {
				if (c == '\0') {
					p = savep, q = saveq;
					c = '[';
					goto dft;
				}
				if (c == '[' && *p == ':') {
					found |= match_charclass(p, chr, &end);
					if (end != NULL) {
						p = end;
						continue;
					}
				}
				if (c == CTLESC)
					c = *p++;
				if (localeisutf8 && c & 0x80) {
					p--;
					wc = get_wc(&p);
					if (wc == 0) /* bad utf-8 */
						return 0;
				} else
					wc = (unsigned char)c;
				if (*p == '-' && p[1] != ']') {
					p++;
					if (*p == CTLESC)
						p++;
					if (localeisutf8) {
						wc2 = get_wc(&p);
						if (wc2 == 0) /* bad utf-8 */
							return 0;
					} else
						wc2 = (unsigned char)*p++;
					if (   collate_range_cmp(chr, wc) >= 0
					    && collate_range_cmp(chr, wc2) <= 0
					   )
						found = 1;
				} else {
					if (chr == wc)
						found = 1;
				}
			} while ((c = *p++) != ']');
			if (found == invert)
				goto backtrack;
			break;
		}
dft:	        default:
			if (*q == '\0')
				return 0;
			if (*q++ == c)
				break;
backtrack:
			/*
			 * If we have a mismatch (other than hitting the end
			 * of the string), go back to the last '*' seen and
			 * have it match one additional character.
			 */
			if (bt_p == NULL)
				return 0;
			if (*bt_q == '\0')
				return 0;
			bt_q++;
			p = bt_p;
			q = bt_q;
			break;
		}
	}
}