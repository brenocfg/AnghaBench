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
struct c_declspecs {int dummy; } ;
struct c_declarator {int dummy; } ;
typedef  int /*<<< orphan*/  c_parser ;
typedef  int /*<<< orphan*/  c_dtr_syn ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_MULT ; 
 int /*<<< orphan*/  CPP_XOR ; 
 struct c_declspecs* build_null_declspecs () ; 
 int /*<<< orphan*/  c_parser_consume_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_declspecs (int /*<<< orphan*/ *,struct c_declspecs*,int,int,int) ; 
 struct c_declarator* c_parser_direct_declarator (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ c_parser_next_token_is (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ flag_blocks ; 
 struct c_declarator* make_block_pointer_declarator (struct c_declspecs*,struct c_declarator*) ; 
 struct c_declarator* make_pointer_declarator (struct c_declspecs*,struct c_declarator*) ; 

__attribute__((used)) static struct c_declarator *
c_parser_declarator (c_parser *parser, bool type_seen_p, c_dtr_syn kind,
		     bool *seen_id)
{
  /* Parse any initial pointer part.  */
  if (c_parser_next_token_is (parser, CPP_MULT))
    {
      struct c_declspecs *quals_attrs = build_null_declspecs ();
      struct c_declarator *inner;
      c_parser_consume_token (parser);
      c_parser_declspecs (parser, quals_attrs, false, false, true);
      inner = c_parser_declarator (parser, type_seen_p, kind, seen_id);
      if (inner == NULL)
	return NULL;
      else
	return make_pointer_declarator (quals_attrs, inner);
    }
  /* APPLE LOCAL begin radar 5732232 - blocks (C++ cc) */
  else if (flag_blocks && c_parser_next_token_is (parser, CPP_XOR)) {
    struct c_declspecs *quals_attrs = build_null_declspecs ();
    struct c_declarator *inner;
    c_parser_consume_token (parser);
    c_parser_declspecs (parser, quals_attrs, false, false, true);
    inner = c_parser_declarator (parser, type_seen_p, kind, seen_id);
    if (inner == NULL)
      return NULL;
    else
      /* APPLE LOCAL radar 5814025 (C++ cc) */
      return make_block_pointer_declarator (quals_attrs, inner);    
  }
  /* APPLE LOCAL end radar 5732232 - blocks (C++ cc) */
  /* Now we have a direct declarator, direct abstract declarator or
     nothing (which counts as a direct abstract declarator here).  */
  return c_parser_direct_declarator (parser, type_seen_p, kind, seen_id);
}