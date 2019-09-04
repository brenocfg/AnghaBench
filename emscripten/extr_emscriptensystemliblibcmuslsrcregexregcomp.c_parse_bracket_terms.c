#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int wchar_t ;
struct TYPE_5__ {char const* s; int cflags; } ;
typedef  TYPE_1__ tre_parse_ctx_t ;
struct TYPE_6__ {int code_min; int code_max; int position; void* class; } ;
typedef  TYPE_2__ tre_literal_t ;
typedef  void* tre_ctype_t ;
struct neg {scalar_t__ len; void** a; scalar_t__ negate; } ;
struct literals {int dummy; } ;
typedef  int /*<<< orphan*/  reg_errcode_t ;

/* Variables and functions */
 int CHARCLASS_NAME_MAX ; 
 scalar_t__ MAX_NEG_CLASSES ; 
 int /*<<< orphan*/  REG_BADPAT ; 
 int /*<<< orphan*/  REG_EBRACK ; 
 int /*<<< orphan*/  REG_ECOLLATE ; 
 int /*<<< orphan*/  REG_ECTYPE ; 
 int /*<<< orphan*/  REG_ERANGE ; 
 int /*<<< orphan*/  REG_ESPACE ; 
 int REG_ICASE ; 
 int /*<<< orphan*/  REG_OK ; 
 int TRE_CHAR_MAX ; 
 scalar_t__ add_icase_literals (struct literals*,int,int) ; 
 int mbtowc (int*,char const*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 void* tre_ctype (char*) ; 
 TYPE_2__* tre_new_lit (struct literals*) ; 

__attribute__((used)) static reg_errcode_t parse_bracket_terms(tre_parse_ctx_t *ctx, const char *s, struct literals *ls, struct neg *neg)
{
	const char *start = s;
	tre_ctype_t class;
	int min, max;
	wchar_t wc;
	int len;

	for (;;) {
		class = 0;
		len = mbtowc(&wc, s, -1);
		if (len <= 0)
			return *s ? REG_BADPAT : REG_EBRACK;
		if (*s == ']' && s != start) {
			ctx->s = s+1;
			return REG_OK;
		}
		if (*s == '-' && s != start && s[1] != ']' &&
		    /* extension: [a-z--@] is accepted as [a-z]|[--@] */
		    (s[1] != '-' || s[2] == ']'))
			return REG_ERANGE;
		if (*s == '[' && (s[1] == '.' || s[1] == '='))
			/* collating symbols and equivalence classes are not supported */
			return REG_ECOLLATE;
		if (*s == '[' && s[1] == ':') {
			char tmp[CHARCLASS_NAME_MAX+1];
			s += 2;
			for (len=0; len < CHARCLASS_NAME_MAX && s[len]; len++) {
				if (s[len] == ':') {
					memcpy(tmp, s, len);
					tmp[len] = 0;
					class = tre_ctype(tmp);
					break;
				}
			}
			if (!class || s[len+1] != ']')
				return REG_ECTYPE;
			min = 0;
			max = TRE_CHAR_MAX;
			s += len+2;
		} else {
			min = max = wc;
			s += len;
			if (*s == '-' && s[1] != ']') {
				s++;
				len = mbtowc(&wc, s, -1);
				max = wc;
				/* XXX - Should use collation order instead of
				   encoding values in character ranges. */
				if (len <= 0 || min > max)
					return REG_ERANGE;
				s += len;
			}
		}

		if (class && neg->negate) {
			if (neg->len >= MAX_NEG_CLASSES)
				return REG_ESPACE;
			neg->a[neg->len++] = class;
		} else  {
			tre_literal_t *lit = tre_new_lit(ls);
			if (!lit)
				return REG_ESPACE;
			lit->code_min = min;
			lit->code_max = max;
			lit->class = class;
			lit->position = -1;

			/* Add opposite-case codepoints if REG_ICASE is present.
			   It seems that POSIX requires that bracket negation
			   should happen before case-folding, but most practical
			   implementations do it the other way around. Changing
			   the order would need efficient representation of
			   case-fold ranges and bracket range sets even with
			   simple patterns so this is ok for now. */
			if (ctx->cflags & REG_ICASE && !class)
				if (add_icase_literals(ls, min, max))
					return REG_ESPACE;
		}
	}
}