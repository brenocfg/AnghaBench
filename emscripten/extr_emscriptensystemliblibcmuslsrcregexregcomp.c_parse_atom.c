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
typedef  int wchar_t ;
struct TYPE_4__ {int cflags; char const* s; int position; char const* re; int /*<<< orphan*/ * n; int /*<<< orphan*/  mem; int /*<<< orphan*/  max_backref; } ;
typedef  TYPE_1__ tre_parse_ctx_t ;
typedef  int /*<<< orphan*/  tre_ast_node_t ;
typedef  int /*<<< orphan*/  reg_errcode_t ;

/* Variables and functions */
 int ASSERTION ; 
 int ASSERT_AT_BOL ; 
 int ASSERT_AT_BOW ; 
 int ASSERT_AT_EOL ; 
 int ASSERT_AT_EOW ; 
 int ASSERT_AT_WB ; 
 int ASSERT_AT_WB_NEG ; 
 int BACKREF ; 
 int EMPTY ; 
 int /*<<< orphan*/  MAX (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_BADPAT ; 
 int /*<<< orphan*/  REG_BADRPT ; 
 int /*<<< orphan*/  REG_EBRACE ; 
 int /*<<< orphan*/  REG_EESCAPE ; 
 int /*<<< orphan*/  REG_ESPACE ; 
 int REG_EXTENDED ; 
 int REG_ICASE ; 
 int REG_NEWLINE ; 
 int /*<<< orphan*/  REG_OK ; 
 int TRE_CHAR_MAX ; 
 int hexval (char const) ; 
 int mbtowc (int*,char const*,int) ; 
 int /*<<< orphan*/  parse_bracket (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/ * tre_ast_new_literal (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/ * tre_ast_new_union (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* tre_expand_macro (char const*) ; 
 int /*<<< orphan*/  tre_islower (int) ; 
 int /*<<< orphan*/  tre_isupper (int) ; 
 int tre_tolower (int) ; 
 int tre_toupper (int) ; 

__attribute__((used)) static reg_errcode_t parse_atom(tre_parse_ctx_t *ctx, const char *s)
{
	int len, ere = ctx->cflags & REG_EXTENDED;
	const char *p;
	tre_ast_node_t *node;
	wchar_t wc;
	switch (*s) {
	case '[':
		return parse_bracket(ctx, s+1);
	case '\\':
		p = tre_expand_macro(s+1);
		if (p) {
			/* assume \X expansion is a single atom */
			reg_errcode_t err = parse_atom(ctx, p);
			ctx->s = s+2;
			return err;
		}
		/* extensions: \b, \B, \<, \>, \xHH \x{HHHH} */
		switch (*++s) {
		case 0:
			return REG_EESCAPE;
		case 'b':
			node = tre_ast_new_literal(ctx->mem, ASSERTION, ASSERT_AT_WB, -1);
			break;
		case 'B':
			node = tre_ast_new_literal(ctx->mem, ASSERTION, ASSERT_AT_WB_NEG, -1);
			break;
		case '<':
			node = tre_ast_new_literal(ctx->mem, ASSERTION, ASSERT_AT_BOW, -1);
			break;
		case '>':
			node = tre_ast_new_literal(ctx->mem, ASSERTION, ASSERT_AT_EOW, -1);
			break;
		case 'x':
			s++;
			int i, v = 0, c;
			len = 2;
			if (*s == '{') {
				len = 8;
				s++;
			}
			for (i=0; i<len && v<0x110000; i++) {
				c = hexval(s[i]);
				if (c < 0) break;
				v = 16*v + c;
			}
			s += i;
			if (len == 8) {
				if (*s != '}')
					return REG_EBRACE;
				s++;
			}
			node = tre_ast_new_literal(ctx->mem, v, v, ctx->position++);
			s--;
			break;
		case '{':
		case '+':
		case '?':
			/* extension: treat \+, \? as repetitions in BRE */
			/* reject repetitions after empty expression in BRE */
			if (!ere)
				return REG_BADRPT;
		case '|':
			/* extension: treat \| as alternation in BRE */
			if (!ere) {
				node = tre_ast_new_literal(ctx->mem, EMPTY, -1, -1);
				s--;
				goto end;
			}
			/* fallthrough */
		default:
			if (!ere && (unsigned)*s-'1' < 9) {
				/* back reference */
				int val = *s - '0';
				node = tre_ast_new_literal(ctx->mem, BACKREF, val, ctx->position++);
				ctx->max_backref = MAX(val, ctx->max_backref);
			} else {
				/* extension: accept unknown escaped char
				   as a literal */
				goto parse_literal;
			}
		}
		s++;
		break;
	case '.':
		if (ctx->cflags & REG_NEWLINE) {
			tre_ast_node_t *tmp1, *tmp2;
			tmp1 = tre_ast_new_literal(ctx->mem, 0, '\n'-1, ctx->position++);
			tmp2 = tre_ast_new_literal(ctx->mem, '\n'+1, TRE_CHAR_MAX, ctx->position++);
			if (tmp1 && tmp2)
				node = tre_ast_new_union(ctx->mem, tmp1, tmp2);
			else
				node = 0;
		} else {
			node = tre_ast_new_literal(ctx->mem, 0, TRE_CHAR_MAX, ctx->position++);
		}
		s++;
		break;
	case '^':
		/* '^' has a special meaning everywhere in EREs, and at beginning of BRE. */
		if (!ere && s != ctx->re)
			goto parse_literal;
		node = tre_ast_new_literal(ctx->mem, ASSERTION, ASSERT_AT_BOL, -1);
		s++;
		break;
	case '$':
		/* '$' is special everywhere in EREs, and in the end of the string in BREs. */
		if (!ere && s[1])
			goto parse_literal;
		node = tre_ast_new_literal(ctx->mem, ASSERTION, ASSERT_AT_EOL, -1);
		s++;
		break;
	case '*':
	case '{':
	case '+':
	case '?':
		/* reject repetitions after empty expression in ERE */
		if (ere)
			return REG_BADRPT;
	case '|':
		if (!ere)
			goto parse_literal;
	case 0:
		node = tre_ast_new_literal(ctx->mem, EMPTY, -1, -1);
		break;
	default:
parse_literal:
		len = mbtowc(&wc, s, -1);
		if (len < 0)
			return REG_BADPAT;
		if (ctx->cflags & REG_ICASE && (tre_isupper(wc) || tre_islower(wc))) {
			tre_ast_node_t *tmp1, *tmp2;
			/* multiple opposite case characters are not supported */
			tmp1 = tre_ast_new_literal(ctx->mem, tre_toupper(wc), tre_toupper(wc), ctx->position);
			tmp2 = tre_ast_new_literal(ctx->mem, tre_tolower(wc), tre_tolower(wc), ctx->position);
			if (tmp1 && tmp2)
				node = tre_ast_new_union(ctx->mem, tmp1, tmp2);
			else
				node = 0;
		} else {
			node = tre_ast_new_literal(ctx->mem, wc, wc, ctx->position);
		}
		ctx->position++;
		s += len;
		break;
	}
end:
	if (!node)
		return REG_ESPACE;
	ctx->n = node;
	ctx->s = s;
	return REG_OK;
}