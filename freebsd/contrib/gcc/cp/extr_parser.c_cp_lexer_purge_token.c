#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  value; } ;
struct TYPE_7__ {scalar_t__ type; int /*<<< orphan*/  keyword; TYPE_1__ u; int /*<<< orphan*/  location; } ;
typedef  TYPE_2__ cp_token ;
struct TYPE_8__ {TYPE_2__* next_token; TYPE_2__* last_token; } ;
typedef  TYPE_3__ cp_lexer ;

/* Variables and functions */
 scalar_t__ CPP_PURGED ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  RID_MAX ; 
 int /*<<< orphan*/  UNKNOWN_LOCATION ; 
 TYPE_2__ eof_token ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

__attribute__((used)) static void
cp_lexer_purge_token (cp_lexer *lexer)
{
  cp_token *tok = lexer->next_token;

  gcc_assert (tok != &eof_token);
  tok->type = CPP_PURGED;
  tok->location = UNKNOWN_LOCATION;
  tok->u.value = NULL_TREE;
  tok->keyword = RID_MAX;

  do
    {
      tok++;
      if (tok == lexer->last_token)
	{
	  tok = (cp_token *)&eof_token;
	  break;
	}
    }
  while (tok->type == CPP_PURGED);
  lexer->next_token = tok;
}