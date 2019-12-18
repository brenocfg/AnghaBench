#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct answer {unsigned int count; int /*<<< orphan*/ * next; TYPE_1__* first; } ;
struct TYPE_9__ {scalar_t__ type; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ cpp_token ;
struct TYPE_10__ {int /*<<< orphan*/  a_buff; } ;
typedef  TYPE_2__ cpp_reader ;

/* Variables and functions */
 scalar_t__ BUFF_FRONT (int /*<<< orphan*/ ) ; 
 size_t BUFF_ROOM (int /*<<< orphan*/ ) ; 
 scalar_t__ CPP_CLOSE_PAREN ; 
 int /*<<< orphan*/  CPP_DL_ERROR ; 
 scalar_t__ CPP_EOF ; 
 scalar_t__ CPP_OPEN_PAREN ; 
 int /*<<< orphan*/  PREV_WHITE ; 
 int T_IF ; 
 int T_UNASSERT ; 
 int /*<<< orphan*/  _cpp_backup_tokens (TYPE_2__*,int) ; 
 int /*<<< orphan*/  _cpp_extend_buff (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cpp_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* cpp_get_token (TYPE_2__*) ; 

__attribute__((used)) static int
parse_answer (cpp_reader *pfile, struct answer **answerp, int type)
{
  const cpp_token *paren;
  struct answer *answer;
  unsigned int acount;

  /* In a conditional, it is legal to not have an open paren.  We
     should save the following token in this case.  */
  paren = cpp_get_token (pfile);

  /* If not a paren, see if we're OK.  */
  if (paren->type != CPP_OPEN_PAREN)
    {
      /* In a conditional no answer is a test for any answer.  It
         could be followed by any token.  */
      if (type == T_IF)
	{
	  _cpp_backup_tokens (pfile, 1);
	  return 0;
	}

      /* #unassert with no answer is valid - it removes all answers.  */
      if (type == T_UNASSERT && paren->type == CPP_EOF)
	return 0;

      cpp_error (pfile, CPP_DL_ERROR, "missing '(' after predicate");
      return 1;
    }

  for (acount = 0;; acount++)
    {
      size_t room_needed;
      const cpp_token *token = cpp_get_token (pfile);
      cpp_token *dest;

      if (token->type == CPP_CLOSE_PAREN)
	break;

      if (token->type == CPP_EOF)
	{
	  cpp_error (pfile, CPP_DL_ERROR, "missing ')' to complete answer");
	  return 1;
	}

      /* struct answer includes the space for one token.  */
      room_needed = (sizeof (struct answer) + acount * sizeof (cpp_token));

      if (BUFF_ROOM (pfile->a_buff) < room_needed)
	_cpp_extend_buff (pfile, &pfile->a_buff, sizeof (struct answer));

      dest = &((struct answer *) BUFF_FRONT (pfile->a_buff))->first[acount];
      *dest = *token;

      /* Drop whitespace at start, for answer equivalence purposes.  */
      if (acount == 0)
	dest->flags &= ~PREV_WHITE;
    }

  if (acount == 0)
    {
      cpp_error (pfile, CPP_DL_ERROR, "predicate's answer is empty");
      return 1;
    }

  answer = (struct answer *) BUFF_FRONT (pfile->a_buff);
  answer->count = acount;
  answer->next = NULL;
  *answerp = answer;

  return 0;
}