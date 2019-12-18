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
struct type {int is_enum; int is_bits; int /*<<< orphan*/  syntax; } ;
struct node {int dummy; } ;
typedef  enum tok { ____Placeholder_tok } tok ;

/* Variables and functions */
 int TOK_BITS ; 
 int TOK_ENUM ; 
 scalar_t__ TOK_FILENAME ; 
 int TOK_INCLUDE ; 
 scalar_t__ TOK_STR ; 
 int TOK_TYPEDEF ; 
 scalar_t__ gettoken () ; 
 int /*<<< orphan*/  input_fopen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct type* make_type (int /*<<< orphan*/ ) ; 
 struct node* parse (int) ; 
 int /*<<< orphan*/  parse_type (int*,struct type*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pushback (int) ; 
 int /*<<< orphan*/  report (char*) ; 
 int /*<<< orphan*/  str ; 
 int /*<<< orphan*/  val ; 

__attribute__((used)) static struct node *
parse_top(enum tok tok)
{
	struct type *t;

	if (tok == '(')
		return (parse(tok));

	if (tok == TOK_TYPEDEF) {
		if (gettoken() != TOK_STR)
			report("type name expected after typedef");

		t = make_type(str);

		tok = gettoken();
		t->is_enum = (tok == TOK_ENUM);
		t->is_bits = (tok == TOK_BITS);

		t->syntax = parse_type(&tok, t, NULL, NULL);
		pushback(tok);

		return (NULL);
	}

	if (tok == TOK_INCLUDE) {
		if (gettoken() != TOK_FILENAME)
			report("filename expected in include directive");

		input_fopen(str, val);
		return (NULL);
	}

	report("'(' or 'typedef' expected");
}