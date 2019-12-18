#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uchar_t ;
struct TYPE_4__ {scalar_t__* dt_options; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
typedef  scalar_t__ caddr_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t DTRACEOPT_RAWBYTES ; 
 scalar_t__ DTRACEOPT_UNSET ; 
 char* alloca (size_t) ; 
 int /*<<< orphan*/  bcopy (char*,char*,size_t) ; 
 scalar_t__ dt_printf (TYPE_1__*,int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ isprint (char) ; 
 scalar_t__ isspace (char) ; 

__attribute__((used)) static int
dt_print_bytes(dtrace_hdl_t *dtp, FILE *fp, caddr_t addr,
    size_t nbytes, int width, int quiet, int forceraw)
{
	/*
	 * If the byte stream is a series of printable characters, followed by
	 * a terminating byte, we print it out as a string.  Otherwise, we
	 * assume that it's something else and just print the bytes.
	 */
	int i, j, margin = 5;
	char *c = (char *)addr;

	if (nbytes == 0)
		return (0);

	if (forceraw)
		goto raw;

	if (dtp->dt_options[DTRACEOPT_RAWBYTES] != DTRACEOPT_UNSET)
		goto raw;

	for (i = 0; i < nbytes; i++) {
		/*
		 * We define a "printable character" to be one for which
		 * isprint(3C) returns non-zero, isspace(3C) returns non-zero,
		 * or a character which is either backspace or the bell.
		 * Backspace and the bell are regrettably special because
		 * they fail the first two tests -- and yet they are entirely
		 * printable.  These are the only two control characters that
		 * have meaning for the terminal and for which isprint(3C) and
		 * isspace(3C) return 0.
		 */
		if (isprint(c[i]) || isspace(c[i]) ||
		    c[i] == '\b' || c[i] == '\a')
			continue;

		if (c[i] == '\0' && i > 0) {
			/*
			 * This looks like it might be a string.  Before we
			 * assume that it is indeed a string, check the
			 * remainder of the byte range; if it contains
			 * additional non-nul characters, we'll assume that
			 * it's a binary stream that just happens to look like
			 * a string, and we'll print out the individual bytes.
			 */
			for (j = i + 1; j < nbytes; j++) {
				if (c[j] != '\0')
					break;
			}

			if (j != nbytes)
				break;

			if (quiet) {
				return (dt_printf(dtp, fp, "%s", c));
			} else {
				return (dt_printf(dtp, fp, " %s%*s",
				    width < 0 ? " " : "", width, c));
			}
		}

		break;
	}

	if (i == nbytes) {
		/*
		 * The byte range is all printable characters, but there is
		 * no trailing nul byte.  We'll assume that it's a string and
		 * print it as such.
		 */
		char *s = alloca(nbytes + 1);
		bcopy(c, s, nbytes);
		s[nbytes] = '\0';
		return (dt_printf(dtp, fp, "  %-*s", width, s));
	}

raw:
	if (dt_printf(dtp, fp, "\n%*s      ", margin, "") < 0)
		return (-1);

	for (i = 0; i < 16; i++)
		if (dt_printf(dtp, fp, "  %c", "0123456789abcdef"[i]) < 0)
			return (-1);

	if (dt_printf(dtp, fp, "  0123456789abcdef\n") < 0)
		return (-1);


	for (i = 0; i < nbytes; i += 16) {
		if (dt_printf(dtp, fp, "%*s%5x:", margin, "", i) < 0)
			return (-1);

		for (j = i; j < i + 16 && j < nbytes; j++) {
			if (dt_printf(dtp, fp, " %02x", (uchar_t)c[j]) < 0)
				return (-1);
		}

		while (j++ % 16) {
			if (dt_printf(dtp, fp, "   ") < 0)
				return (-1);
		}

		if (dt_printf(dtp, fp, "  ") < 0)
			return (-1);

		for (j = i; j < i + 16 && j < nbytes; j++) {
			if (dt_printf(dtp, fp, "%c",
			    c[j] < ' ' || c[j] > '~' ? '.' : c[j]) < 0)
				return (-1);
		}

		if (dt_printf(dtp, fp, "\n") < 0)
			return (-1);
	}

	return (0);
}