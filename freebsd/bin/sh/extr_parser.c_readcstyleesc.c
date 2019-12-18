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
 scalar_t__ CCTL ; 
 int /*<<< orphan*/  CHECKSTRSPACE (int,char*) ; 
 int CTLESC ; 
 int PEOF ; 
 scalar_t__* SQSYNTAX ; 
 int /*<<< orphan*/  USTPUTC (int,char*) ; 
 scalar_t__ doprompt ; 
 int /*<<< orphan*/  initial_localeisutf8 ; 
 char pgetc () ; 
 int /*<<< orphan*/  plinno ; 
 int /*<<< orphan*/  pungetc () ; 
 int /*<<< orphan*/  setprompt (int) ; 
 int /*<<< orphan*/  synerror (char*) ; 

__attribute__((used)) static char *
readcstyleesc(char *out)
{
	int c, vc, i, n;
	unsigned int v;

	c = pgetc();
	switch (c) {
	case '\0':
		synerror("Unterminated quoted string");
	case '\n':
		plinno++;
		if (doprompt)
			setprompt(2);
		else
			setprompt(0);
		return out;
	case '\\':
	case '\'':
	case '"':
		v = c;
		break;
	case 'a': v = '\a'; break;
	case 'b': v = '\b'; break;
	case 'e': v = '\033'; break;
	case 'f': v = '\f'; break;
	case 'n': v = '\n'; break;
	case 'r': v = '\r'; break;
	case 't': v = '\t'; break;
	case 'v': v = '\v'; break;
	case 'x':
		  v = 0;
		  for (;;) {
			  c = pgetc();
			  if (c >= '0' && c <= '9')
				  v = (v << 4) + c - '0';
			  else if (c >= 'A' && c <= 'F')
				  v = (v << 4) + c - 'A' + 10;
			  else if (c >= 'a' && c <= 'f')
				  v = (v << 4) + c - 'a' + 10;
			  else
				  break;
		  }
		  pungetc();
		  break;
	case '0': case '1': case '2': case '3':
	case '4': case '5': case '6': case '7':
		  v = c - '0';
		  c = pgetc();
		  if (c >= '0' && c <= '7') {
			  v <<= 3;
			  v += c - '0';
			  c = pgetc();
			  if (c >= '0' && c <= '7') {
				  v <<= 3;
				  v += c - '0';
			  } else
				  pungetc();
		  } else
			  pungetc();
		  break;
	case 'c':
		  c = pgetc();
		  if (c < 0x3f || c > 0x7a || c == 0x60)
			  synerror("Bad escape sequence");
		  if (c == '\\' && pgetc() != '\\')
			  synerror("Bad escape sequence");
		  if (c == '?')
			  v = 127;
		  else
			  v = c & 0x1f;
		  break;
	case 'u':
	case 'U':
		  n = c == 'U' ? 8 : 4;
		  v = 0;
		  for (i = 0; i < n; i++) {
			  c = pgetc();
			  if (c >= '0' && c <= '9')
				  v = (v << 4) + c - '0';
			  else if (c >= 'A' && c <= 'F')
				  v = (v << 4) + c - 'A' + 10;
			  else if (c >= 'a' && c <= 'f')
				  v = (v << 4) + c - 'a' + 10;
			  else
				  synerror("Bad escape sequence");
		  }
		  if (v == 0 || (v >= 0xd800 && v <= 0xdfff))
			  synerror("Bad escape sequence");
		  /* We really need iconv here. */
		  if (initial_localeisutf8 && v > 127) {
			  CHECKSTRSPACE(4, out);
			  /*
			   * We cannot use wctomb() as the locale may have
			   * changed.
			   */
			  if (v <= 0x7ff) {
				  USTPUTC(0xc0 | v >> 6, out);
				  USTPUTC(0x80 | (v & 0x3f), out);
				  return out;
			  } else if (v <= 0xffff) {
				  USTPUTC(0xe0 | v >> 12, out);
				  USTPUTC(0x80 | ((v >> 6) & 0x3f), out);
				  USTPUTC(0x80 | (v & 0x3f), out);
				  return out;
			  } else if (v <= 0x10ffff) {
				  USTPUTC(0xf0 | v >> 18, out);
				  USTPUTC(0x80 | ((v >> 12) & 0x3f), out);
				  USTPUTC(0x80 | ((v >> 6) & 0x3f), out);
				  USTPUTC(0x80 | (v & 0x3f), out);
				  return out;
			  }
		  }
		  if (v > 127)
			  v = '?';
		  break;
	default:
		  synerror("Bad escape sequence");
	}
	vc = (char)v;
	/*
	 * We can't handle NUL bytes.
	 * POSIX says we should skip till the closing quote.
	 */
	if (vc == '\0') {
		while ((c = pgetc()) != '\'') {
			if (c == '\\')
				c = pgetc();
			if (c == PEOF)
				synerror("Unterminated quoted string");
			if (c == '\n') {
				plinno++;
				if (doprompt)
					setprompt(2);
				else
					setprompt(0);
			}
		}
		pungetc();
		return out;
	}
	if (SQSYNTAX[vc] == CCTL)
		USTPUTC(CTLESC, out);
	USTPUTC(vc, out);
	return out;
}