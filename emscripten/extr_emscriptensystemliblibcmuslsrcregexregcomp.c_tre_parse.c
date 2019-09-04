#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tre_stack_t ;
struct TYPE_5__ {int cflags; char* re; char* s; int submatch_id; int /*<<< orphan*/  mem; void* n; int /*<<< orphan*/ * stack; } ;
typedef  TYPE_1__ tre_parse_ctx_t ;
typedef  int /*<<< orphan*/  tre_ast_node_t ;
typedef  scalar_t__ reg_errcode_t ;

/* Variables and functions */
 int /*<<< orphan*/  EMPTY ; 
 int /*<<< orphan*/  PUSHINT (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUSHPTR (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ REG_BADBR ; 
 scalar_t__ REG_EPAREN ; 
 scalar_t__ REG_ESPACE ; 
 int REG_EXTENDED ; 
 scalar_t__ REG_OK ; 
 scalar_t__ marksub (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ parse_atom (TYPE_1__*,char const*) ; 
 char* parse_dup (char const*,int,int*,int*) ; 
 int /*<<< orphan*/ * tre_ast_new_catenation (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 void* tre_ast_new_iter (int /*<<< orphan*/ ,void*,int,int,int /*<<< orphan*/ ) ; 
 void* tre_ast_new_literal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ * tre_ast_new_union (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tre_stack_pop_int (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tre_stack_pop_voidptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static reg_errcode_t tre_parse(tre_parse_ctx_t *ctx)
{
	tre_ast_node_t *nbranch=0, *nunion=0;
	int ere = ctx->cflags & REG_EXTENDED;
	const char *s = ctx->re;
	int subid = 0;
	int depth = 0;
	reg_errcode_t err;
	tre_stack_t *stack = ctx->stack;

	PUSHINT(err, stack, subid++);
	for (;;) {
		if ((!ere && *s == '\\' && s[1] == '(') ||
		    (ere && *s == '(')) {
			PUSHPTR(err, stack, nunion);
			PUSHPTR(err, stack, nbranch);
			PUSHINT(err, stack, subid++);
			s++;
			if (!ere)
				s++;
			depth++;
			nbranch = nunion = 0;
			continue;
		}
		if ((!ere && *s == '\\' && s[1] == ')') ||
		    (ere && *s == ')' && depth)) {
			ctx->n = tre_ast_new_literal(ctx->mem, EMPTY, -1, -1);
			if (!ctx->n)
				return REG_ESPACE;
		} else {
			err = parse_atom(ctx, s);
			if (err != REG_OK)
				return err;
			s = ctx->s;
		}

	parse_iter:
		for (;;) {
			int min, max;

			if (*s!='\\' && *s!='*') {
				if (!ere)
					break;
				if (*s!='+' && *s!='?' && *s!='{')
					break;
			}
			if (*s=='\\' && ere)
				break;
			/* extension: treat \+, \? as repetitions in BRE */
			if (*s=='\\' && s[1]!='+' && s[1]!='?' && s[1]!='{')
				break;
			if (*s=='\\')
				s++;

			/* handle ^* at the start of a complete BRE. */
			if (!ere && s==ctx->re+1 && s[-1]=='^')
				break;

			/* extension: multiple consecutive *+?{,} is unspecified,
			   but (a+)+ has to be supported so accepting a++ makes
			   sense, note however that the RE_DUP_MAX limit can be
			   circumvented: (a{255}){255} uses a lot of memory.. */
			if (*s=='{') {
				s = parse_dup(s+1, ere, &min, &max);
				if (!s)
					return REG_BADBR;
			} else {
				min=0;
				max=-1;
				if (*s == '+')
					min = 1;
				if (*s == '?')
					max = 1;
				s++;
			}
			if (max == 0)
				ctx->n = tre_ast_new_literal(ctx->mem, EMPTY, -1, -1);
			else
				ctx->n = tre_ast_new_iter(ctx->mem, ctx->n, min, max, 0);
			if (!ctx->n)
				return REG_ESPACE;
		}

		nbranch = tre_ast_new_catenation(ctx->mem, nbranch, ctx->n);
		if ((ere && *s == '|') ||
		    (ere && *s == ')' && depth) ||
		    (!ere && *s == '\\' && s[1] == ')') ||
		    /* extension: treat \| as alternation in BRE */
		    (!ere && *s == '\\' && s[1] == '|') ||
		    !*s) {
			/* extension: empty branch is unspecified (), (|a), (a|)
			   here they are not rejected but match on empty string */
			int c = *s;
			nunion = tre_ast_new_union(ctx->mem, nunion, nbranch);
			nbranch = 0;

			if (c == '\\' && s[1] == '|') {
				s+=2;
			} else if (c == '|') {
				s++;
			} else {
				if (c == '\\') {
					if (!depth) return REG_EPAREN;
					s+=2;
				} else if (c == ')')
					s++;
				depth--;
				err = marksub(ctx, nunion, tre_stack_pop_int(stack));
				if (err != REG_OK)
					return err;
				if (!c && depth<0) {
					ctx->submatch_id = subid;
					return REG_OK;
				}
				if (!c || depth<0)
					return REG_EPAREN;
				nbranch = tre_stack_pop_voidptr(stack);
				nunion = tre_stack_pop_voidptr(stack);
				goto parse_iter;
			}
		}
	}
}