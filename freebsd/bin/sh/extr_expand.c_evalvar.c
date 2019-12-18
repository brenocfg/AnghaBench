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
struct worddest {int /*<<< orphan*/  state; } ;
struct nodelist {struct nodelist* next; } ;
typedef  int ptrdiff_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int CTLBACKQ ; 
 char const CTLENDVAR ; 
 int CTLESC ; 
 int CTLQUOTE ; 
 int CTLVAR ; 
 int EXP_LIT_QUOTED ; 
 int EXP_SPLIT ; 
 int EXP_SPLIT_LIT ; 
 int /*<<< orphan*/  STADJUST (int,char const*) ; 
 int /*<<< orphan*/  STPUTC (char,char const*) ; 
#define  VSASSIGN 138 
#define  VSERROR 137 
#define  VSLENGTH 136 
 int VSLINENO ; 
#define  VSMINUS 135 
#define  VSNORMAL 134 
 int VSNUL ; 
#define  VSPLUS 133 
#define  VSQUESTION 132 
 int VSQUOTE ; 
#define  VSTRIMLEFT 131 
#define  VSTRIMLEFTMAX 130 
#define  VSTRIMRIGHT 129 
#define  VSTRIMRIGHTMAX 128 
 int VSTYPE ; 
 int /*<<< orphan*/  WORD_QUOTEMARK ; 
 int /*<<< orphan*/  abort () ; 
 char const* argstr (char const*,struct nodelist**,int,struct worddest*) ; 
 char* bltinlookup (char const*,int) ; 
 int /*<<< orphan*/  cvtnum (int,char*) ; 
 int /*<<< orphan*/  error (char*,int,char const*,...) ; 
 char const* expdest ; 
 int /*<<< orphan*/  is_name (char const) ; 
 scalar_t__ localeisutf8 ; 
 char* lookupvar (char const*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  reprocess (int,int,int const,int,struct worddest*) ; 
 char const* stackblock () ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strtodest (char const*,int,int const,int,struct worddest*) ; 
 char* subevalvar_misc (char const*,struct nodelist**,char const*,int,int,int) ; 
 char* subevalvar_trim (char const*,struct nodelist**,int,int,int) ; 
 scalar_t__ uflag ; 
 int varisset (char const*,int) ; 
 int /*<<< orphan*/  varvalue (char const*,int,int,int,struct worddest*) ; 

__attribute__((used)) static const char *
evalvar(const char *p, struct nodelist **restrict argbackq, int flag,
    struct worddest *dst)
{
	int subtype;
	int varflags;
	const char *var;
	const char *val;
	int patloc;
	int c;
	int set;
	int special;
	int startloc;
	int varlen;
	int varlenb;
	char buf[21];

	varflags = (unsigned char)*p++;
	subtype = varflags & VSTYPE;
	var = p;
	special = 0;
	if (! is_name(*p))
		special = 1;
	p = strchr(p, '=') + 1;
	if (varflags & VSLINENO) {
		set = 1;
		special = 1;
		val = NULL;
	} else if (special) {
		set = varisset(var, varflags & VSNUL);
		val = NULL;
	} else {
		val = bltinlookup(var, 1);
		if (val == NULL || ((varflags & VSNUL) && val[0] == '\0')) {
			val = NULL;
			set = 0;
		} else
			set = 1;
	}
	varlen = 0;
	startloc = expdest - stackblock();
	if (!set && uflag && *var != '@' && *var != '*') {
		switch (subtype) {
		case VSNORMAL:
		case VSTRIMLEFT:
		case VSTRIMLEFTMAX:
		case VSTRIMRIGHT:
		case VSTRIMRIGHTMAX:
		case VSLENGTH:
			error("%.*s: parameter not set", (int)(p - var - 1),
			    var);
		}
	}
	if (set && subtype != VSPLUS) {
		/* insert the value of the variable */
		if (special) {
			if (varflags & VSLINENO) {
				if (p - var > (ptrdiff_t)sizeof(buf))
					abort();
				memcpy(buf, var, p - var - 1);
				buf[p - var - 1] = '\0';
				strtodest(buf, flag, subtype,
				    varflags & VSQUOTE, dst);
			} else
				varvalue(var, varflags & VSQUOTE, subtype, flag,
				    dst);
			if (subtype == VSLENGTH) {
				varlenb = expdest - stackblock() - startloc;
				varlen = varlenb;
				if (localeisutf8) {
					val = stackblock() + startloc;
					for (;val != expdest; val++)
						if ((*val & 0xC0) == 0x80)
							varlen--;
				}
				STADJUST(-varlenb, expdest);
			}
		} else {
			if (subtype == VSLENGTH) {
				for (;*val; val++)
					if (!localeisutf8 ||
					    (*val & 0xC0) != 0x80)
						varlen++;
			}
			else
				strtodest(val, flag, subtype,
				    varflags & VSQUOTE, dst);
		}
	}

	if (subtype == VSPLUS)
		set = ! set;

	switch (subtype) {
	case VSLENGTH:
		cvtnum(varlen, buf);
		strtodest(buf, flag, VSNORMAL, varflags & VSQUOTE, dst);
		break;

	case VSNORMAL:
		return p;

	case VSPLUS:
	case VSMINUS:
		if (!set) {
			return argstr(p, argbackq,
			    flag | (flag & EXP_SPLIT ? EXP_SPLIT_LIT : 0) |
			    (varflags & VSQUOTE ? EXP_LIT_QUOTED : 0), dst);
		}
		break;

	case VSTRIMLEFT:
	case VSTRIMLEFTMAX:
	case VSTRIMRIGHT:
	case VSTRIMRIGHTMAX:
		if (!set)
			break;
		/*
		 * Terminate the string and start recording the pattern
		 * right after it
		 */
		STPUTC('\0', expdest);
		patloc = expdest - stackblock();
		p = subevalvar_trim(p, argbackq, patloc, subtype, startloc);
		reprocess(startloc, flag, VSNORMAL, varflags & VSQUOTE, dst);
		if (flag & EXP_SPLIT && *var == '@' && varflags & VSQUOTE)
			dst->state = WORD_QUOTEMARK;
		return p;

	case VSASSIGN:
	case VSQUESTION:
		if (!set) {
			p = subevalvar_misc(p, argbackq, var, subtype,
			    startloc, varflags);
			/* assert(subtype == VSASSIGN); */
			val = lookupvar(var);
			strtodest(val, flag, subtype, varflags & VSQUOTE, dst);
			return p;
		}
		break;

	case VSERROR:
		c = p - var - 1;
		error("${%.*s%s}: Bad substitution", c, var,
		    (c > 0 && *p != CTLENDVAR) ? "..." : "");

	default:
		abort();
	}

	{	/* skip to end of alternative */
		int nesting = 1;
		for (;;) {
			if ((c = *p++) == CTLESC)
				p++;
			else if (c == CTLBACKQ || c == (CTLBACKQ|CTLQUOTE))
				*argbackq = (*argbackq)->next;
			else if (c == CTLVAR) {
				if ((*p++ & VSTYPE) != VSNORMAL)
					nesting++;
			} else if (c == CTLENDVAR) {
				if (--nesting == 0)
					break;
			}
		}
	}
	return p;
}