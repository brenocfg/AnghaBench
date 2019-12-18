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
typedef  enum token { ____Placeholder_token } token ;

/* Variables and functions */
 scalar_t__ BINOP ; 
 int EOI ; 
#define  FILTT 130 
 int LPAREN ; 
 int RPAREN ; 
#define  STREZ 129 
#define  STRNZ 128 
 scalar_t__ TOKEN_TYPE (int) ; 
 scalar_t__ UNOP ; 
 int binop (int) ; 
 int filstat (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  getn (int /*<<< orphan*/ *) ; 
 int isatty (int /*<<< orphan*/ ) ; 
 scalar_t__ nargc ; 
 int oexpr (int) ; 
 int /*<<< orphan*/  parenlevel ; 
 scalar_t__ strlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  syntax (int /*<<< orphan*/ *,char*) ; 
 int t_lex (scalar_t__) ; 
 int /*<<< orphan*/ ** t_wp ; 

__attribute__((used)) static int
primary(enum token n)
{
	enum token nn;
	int res;

	if (n == EOI)
		return 0;		/* missing expression */
	if (n == LPAREN) {
		parenlevel++;
		if ((nn = t_lex(nargc > 0 ? (--nargc, *++t_wp) : NULL)) ==
		    RPAREN) {
			parenlevel--;
			return 0;	/* missing expression */
		}
		res = oexpr(nn);
		if (t_lex(nargc > 0 ? (--nargc, *++t_wp) : NULL) != RPAREN)
			syntax(NULL, "closing paren expected");
		parenlevel--;
		return res;
	}
	if (TOKEN_TYPE(n) == UNOP) {
		/* unary expression */
		if (--nargc == 0)
			syntax(NULL, "argument expected"); /* impossible */
		switch (n) {
		case STREZ:
			return strlen(*++t_wp) == 0;
		case STRNZ:
			return strlen(*++t_wp) != 0;
		case FILTT:
			return isatty(getn(*++t_wp));
		default:
			return filstat(*++t_wp, n);
		}
	}

	nn = t_lex(nargc > 0 ? t_wp[1] : NULL);
	if (TOKEN_TYPE(nn) == BINOP)
		return binop(nn);

	return strlen(*t_wp) > 0;
}