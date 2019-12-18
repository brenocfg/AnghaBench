#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ wint_t ;
typedef  int /*<<< orphan*/  mbstate_t ;
struct TYPE_12__ {int /*<<< orphan*/  _mbstate; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 scalar_t__ EILSEQ ; 
 int EOF ; 
 scalar_t__ WEOF ; 
 int /*<<< orphan*/  bflag ; 
 int /*<<< orphan*/  clearerr (TYPE_1__*) ; 
 scalar_t__ eflag ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 scalar_t__ feof (TYPE_1__*) ; 
 scalar_t__ ferror (TYPE_1__*) ; 
 int /*<<< orphan*/  filename ; 
 int /*<<< orphan*/  fprintf (TYPE_1__*,char*,...) ; 
 int getc (TYPE_1__*) ; 
 scalar_t__ getwc (TYPE_1__*) ; 
 int /*<<< orphan*/  iswascii (scalar_t__) ; 
 scalar_t__ iswcntrl (scalar_t__) ; 
 int /*<<< orphan*/  iswprint (scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nflag ; 
 int putchar (int) ; 
 scalar_t__ putwchar (scalar_t__) ; 
 int rval ; 
 scalar_t__ sflag ; 
 TYPE_1__* stdin ; 
 TYPE_1__* stdout ; 
 scalar_t__ tflag ; 
 void* toascii (scalar_t__) ; 
 int /*<<< orphan*/  ungetc (int,TYPE_1__*) ; 
 scalar_t__ vflag ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cook_cat(FILE *fp)
{
	int ch, gobble, line, prev;
	wint_t wch;

	/* Reset EOF condition on stdin. */
	if (fp == stdin && feof(stdin))
		clearerr(stdin);

	line = gobble = 0;
	for (prev = '\n'; (ch = getc(fp)) != EOF; prev = ch) {
		if (prev == '\n') {
			if (sflag) {
				if (ch == '\n') {
					if (gobble)
						continue;
					gobble = 1;
				} else
					gobble = 0;
			}
			if (nflag) {
				if (!bflag || ch != '\n') {
					(void)fprintf(stdout, "%6d\t", ++line);
					if (ferror(stdout))
						break;
				} else if (eflag) {
					(void)fprintf(stdout, "%6s\t", "");
					if (ferror(stdout))
						break;
				}
			}
		}
		if (ch == '\n') {
			if (eflag && putchar('$') == EOF)
				break;
		} else if (ch == '\t') {
			if (tflag) {
				if (putchar('^') == EOF || putchar('I') == EOF)
					break;
				continue;
			}
		} else if (vflag) {
			(void)ungetc(ch, fp);
			/*
			 * Our getwc(3) doesn't change file position
			 * on error.
			 */
			if ((wch = getwc(fp)) == WEOF) {
				if (ferror(fp) && errno == EILSEQ) {
					clearerr(fp);
					/* Resync attempt. */
					memset(&fp->_mbstate, 0, sizeof(mbstate_t));
					if ((ch = getc(fp)) == EOF)
						break;
					wch = ch;
					goto ilseq;
				} else
					break;
			}
			if (!iswascii(wch) && !iswprint(wch)) {
ilseq:
				if (putchar('M') == EOF || putchar('-') == EOF)
					break;
				wch = toascii(wch);
			}
			if (iswcntrl(wch)) {
				ch = toascii(wch);
				ch = (ch == '\177') ? '?' : (ch | 0100);
				if (putchar('^') == EOF || putchar(ch) == EOF)
					break;
				continue;
			}
			if (putwchar(wch) == WEOF)
				break;
			ch = -1;
			continue;
		}
		if (putchar(ch) == EOF)
			break;
	}
	if (ferror(fp)) {
		warn("%s", filename);
		rval = 1;
		clearerr(fp);
	}
	if (ferror(stdout))
		err(1, "stdout");
}