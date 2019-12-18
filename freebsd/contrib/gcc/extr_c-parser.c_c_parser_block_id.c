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
typedef  int /*<<< orphan*/ * tree ;
struct c_declspecs {int /*<<< orphan*/  type_seen_p; int /*<<< orphan*/  declspecs_seen_p; } ;
struct c_declarator {int dummy; } ;
typedef  int /*<<< orphan*/  c_parser ;

/* Variables and functions */
 int /*<<< orphan*/  C_DTR_BLOCK ; 
 struct c_declspecs* build_null_declspecs () ; 
 struct c_declarator* c_parser_declarator (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  c_parser_declspecs (int /*<<< orphan*/ *,struct c_declspecs*,int,int,int) ; 
 int /*<<< orphan*/  c_parser_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  finish_declspecs (struct c_declspecs*) ; 
 int /*<<< orphan*/ * grokblockdecl (struct c_declspecs*,struct c_declarator*) ; 
 int /*<<< orphan*/  pending_xref_error () ; 

__attribute__((used)) static tree
c_parser_block_id (c_parser* parser)
{
  struct c_declspecs *specs = build_null_declspecs ();
  struct c_declarator *declarator;
  bool dummy = false;

  c_parser_declspecs (parser, specs, false, true, true);
  if (!specs->declspecs_seen_p)
    {
      c_parser_error (parser, "expected specifier-qualifier-list");
      return NULL;
    }
  pending_xref_error ();
  finish_declspecs (specs);
  declarator = c_parser_declarator (parser, specs->type_seen_p,
				    C_DTR_BLOCK, &dummy);
  if (declarator == NULL)
    return NULL;

  return grokblockdecl (specs, declarator);
}