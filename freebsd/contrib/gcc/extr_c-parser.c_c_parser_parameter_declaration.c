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
typedef  void* tree ;
struct c_parm {int dummy; } ;
struct c_declspecs {int /*<<< orphan*/  type_seen_p; void* attrs; } ;
struct c_declarator {int dummy; } ;
typedef  int /*<<< orphan*/  c_parser ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_COMMA ; 
 int /*<<< orphan*/  C_DTR_PARM ; 
 void* NULL_TREE ; 
 int /*<<< orphan*/  RID_ATTRIBUTE ; 
 struct c_parm* build_c_parm (struct c_declspecs*,int /*<<< orphan*/ ,struct c_declarator*) ; 
 struct c_declspecs* build_null_declspecs () ; 
 void* c_parser_attributes (int /*<<< orphan*/ *) ; 
 struct c_declarator* c_parser_declarator (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  c_parser_declspecs (int /*<<< orphan*/ *,struct c_declspecs*,int,int,int) ; 
 int /*<<< orphan*/  c_parser_error (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ c_parser_next_token_is_keyword (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_parser_next_token_starts_declspecs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_skip_to_end_of_parameter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_skip_until_found (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chainon (void*,void*) ; 
 int /*<<< orphan*/  declspecs_add_attrs (struct c_declspecs*,void*) ; 
 int /*<<< orphan*/  finish_declspecs (struct c_declspecs*) ; 
 int /*<<< orphan*/  pending_xref_error () ; 

__attribute__((used)) static struct c_parm *
c_parser_parameter_declaration (c_parser *parser, tree attrs)
{
  struct c_declspecs *specs;
  struct c_declarator *declarator;
  tree prefix_attrs;
  tree postfix_attrs = NULL_TREE;
  bool dummy = false;
  if (!c_parser_next_token_starts_declspecs (parser))
    {
      /* ??? In some Objective-C cases '...' isn't applicable so there
	 should be a different message.  */
      c_parser_error (parser,
		      "expected declaration specifiers or %<...%>");
      c_parser_skip_to_end_of_parameter (parser);
      return NULL;
    }
  specs = build_null_declspecs ();
  if (attrs)
    {
      declspecs_add_attrs (specs, attrs);
      attrs = NULL_TREE;
    }
  c_parser_declspecs (parser, specs, true, true, true);
  finish_declspecs (specs);
  pending_xref_error ();
  prefix_attrs = specs->attrs;
  specs->attrs = NULL_TREE;
  declarator = c_parser_declarator (parser, specs->type_seen_p,
				    C_DTR_PARM, &dummy);
  if (declarator == NULL)
    {
      c_parser_skip_until_found (parser, CPP_COMMA, NULL);
      return NULL;
    }
  if (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
    postfix_attrs = c_parser_attributes (parser);
  return build_c_parm (specs, chainon (postfix_attrs, prefix_attrs),
		       declarator);
}