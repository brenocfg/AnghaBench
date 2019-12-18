#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  enum cpp_ttype { ____Placeholder_cpp_ttype } cpp_ttype ;
typedef  char cppchar_t ;
struct TYPE_10__ {char* text; } ;
struct TYPE_7__ {TYPE_4__ str; } ;
struct TYPE_8__ {int type; int flags; TYPE_1__ val; } ;
typedef  TYPE_2__ cpp_token ;
typedef  int /*<<< orphan*/  cpp_reader ;
struct TYPE_9__ {scalar_t__ category; char* name; } ;

/* Variables and functions */
#define  CPP_AND 142 
 int CPP_CHAR ; 
#define  CPP_COLON 141 
#define  CPP_DEREF 140 
#define  CPP_DIV 139 
#define  CPP_DOT 138 
 scalar_t__ CPP_FIRST_DIGRAPH ; 
#define  CPP_GREATER 137 
#define  CPP_HASH 136 
 scalar_t__ CPP_LAST_EQ ; 
#define  CPP_LESS 135 
#define  CPP_MINUS 134 
#define  CPP_MOD 133 
#define  CPP_NAME 132 
#define  CPP_NUMBER 131 
 int /*<<< orphan*/  CPP_OPTION (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  CPP_OR 130 
#define  CPP_OTHER 129 
#define  CPP_PLUS 128 
 int CPP_STRING ; 
 int DIGRAPH ; 
 char EOF ; 
 int NAMED_OP ; 
 scalar_t__ SPELL_OPERATOR ; 
 char** digraph_spellings ; 
 int /*<<< orphan*/  name_p (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  objc ; 
 TYPE_3__* token_spellings ; 

int
cpp_avoid_paste (cpp_reader *pfile, const cpp_token *token1,
		 const cpp_token *token2)
{
  enum cpp_ttype a = token1->type, b = token2->type;
  cppchar_t c;

  if (token1->flags & NAMED_OP)
    a = CPP_NAME;
  if (token2->flags & NAMED_OP)
    b = CPP_NAME;

  c = EOF;
  if (token2->flags & DIGRAPH)
    c = digraph_spellings[(int) b - (int) CPP_FIRST_DIGRAPH][0];
  else if (token_spellings[b].category == SPELL_OPERATOR)
    c = token_spellings[b].name[0];

  /* Quickly get everything that can paste with an '='.  */
  if ((int) a <= (int) CPP_LAST_EQ && c == '=')
    return 1;

  switch (a)
    {
    case CPP_GREATER:	return c == '>';
    case CPP_LESS:	return c == '<' || c == '%' || c == ':';
    case CPP_PLUS:	return c == '+';
    case CPP_MINUS:	return c == '-' || c == '>';
    case CPP_DIV:	return c == '/' || c == '*'; /* Comments.  */
    case CPP_MOD:	return c == ':' || c == '>';
    case CPP_AND:	return c == '&';
    case CPP_OR:	return c == '|';
    case CPP_COLON:	return c == ':' || c == '>';
    case CPP_DEREF:	return c == '*';
    case CPP_DOT:	return c == '.' || c == '%' || b == CPP_NUMBER;
    case CPP_HASH:	return c == '#' || c == '%'; /* Digraph form.  */
    case CPP_NAME:	return ((b == CPP_NUMBER
				 && name_p (pfile, &token2->val.str))
				|| b == CPP_NAME
				|| b == CPP_CHAR || b == CPP_STRING); /* L */
    case CPP_NUMBER:	return (b == CPP_NUMBER || b == CPP_NAME
				|| c == '.' || c == '+' || c == '-');
				      /* UCNs */
    case CPP_OTHER:	return ((token1->val.str.text[0] == '\\'
				 && b == CPP_NAME)
				|| (CPP_OPTION (pfile, objc)
				    && token1->val.str.text[0] == '@'
				    && (b == CPP_NAME || b == CPP_STRING)));
    default:		break;
    }

  return 0;
}