#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int rm_eo; int rm_so; } ;
typedef  TYPE_1__ regmatch_t ;
struct TYPE_11__ {int /*<<< orphan*/  re_nsub; } ;
typedef  TYPE_2__ pattern_t ;
struct TYPE_12__ {int len; } ;
typedef  TYPE_3__ line_t ;

/* Variables and functions */
 int ERR ; 
 int GSG ; 
 int /*<<< orphan*/  NEWLINE_TO_NUL (char*,int) ; 
 int /*<<< orphan*/  NUL_TO_NEWLINE (char*,int) ; 
 int /*<<< orphan*/  REALLOC (scalar_t__,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  REG_NOTBOL ; 
 int SE_MAX ; 
 int apply_subst_template (char*,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 char* errmsg ; 
 char* get_sbuf_line (TYPE_3__*) ; 
 scalar_t__ isbinary ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char*,int) ; 
 scalar_t__ rbuf ; 
 int /*<<< orphan*/  rbufsz ; 
 int /*<<< orphan*/  regexec (TYPE_2__*,char*,int,TYPE_1__*,int /*<<< orphan*/ ) ; 

int
substitute_matching_text(pattern_t *pat, line_t *lp, int gflag, int kth)
{
	int off = 0;
	int changed = 0;
	int matchno = 0;
	int i = 0;
	regmatch_t rm[SE_MAX];
	char *txt;
	char *eot;

	if ((txt = get_sbuf_line(lp)) == NULL)
		return ERR;
	if (isbinary)
		NUL_TO_NEWLINE(txt, lp->len);
	eot = txt + lp->len;
	if (!regexec(pat, txt, SE_MAX, rm, 0)) {
		do {
			if (!kth || kth == ++matchno) {
				changed++;
				i = rm[0].rm_so;
				REALLOC(rbuf, rbufsz, off + i, ERR);
				if (isbinary)
					NEWLINE_TO_NUL(txt, rm[0].rm_eo);
				memcpy(rbuf + off, txt, i);
				off += i;
				if ((off = apply_subst_template(txt, rm, off,
				    pat->re_nsub)) < 0)
					return ERR;
			} else {
				i = rm[0].rm_eo;
				REALLOC(rbuf, rbufsz, off + i, ERR);
				if (isbinary)
					NEWLINE_TO_NUL(txt, i);
				memcpy(rbuf + off, txt, i);
				off += i;
			}
			txt += rm[0].rm_eo;
		} while (*txt &&
                        (!changed || ((gflag & GSG) && rm[0].rm_eo)) &&
		        !regexec(pat, txt, SE_MAX, rm, REG_NOTBOL));
		i = eot - txt;
		REALLOC(rbuf, rbufsz, off + i + 2, ERR);
		if (i > 0 && !rm[0].rm_eo && (gflag & GSG)) {
			errmsg = "infinite substitution loop";
			return  ERR;
		}
		if (isbinary)
			NEWLINE_TO_NUL(txt, i);
		memcpy(rbuf + off, txt, i);
		memcpy(rbuf + off + i, "\n", 2);
	}
	return changed ? off + i + 1 : 0;
}