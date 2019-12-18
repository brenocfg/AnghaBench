#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/ * source; } ;
struct TYPE_14__ {scalar_t__ type; int flags; TYPE_1__ val; } ;
typedef  TYPE_3__ cpp_token ;
struct TYPE_13__ {int parsing_args; } ;
struct TYPE_15__ {TYPE_3__ const eof; TYPE_2__ state; } ;
typedef  TYPE_4__ cpp_reader ;
typedef  int /*<<< orphan*/  cpp_hashnode ;
typedef  int /*<<< orphan*/  _cpp_buff ;

/* Variables and functions */
 scalar_t__ CPP_EOF ; 
 scalar_t__ CPP_OPEN_PAREN ; 
 scalar_t__ CPP_PADDING ; 
 int PREV_WHITE ; 
 int /*<<< orphan*/  _cpp_backup_tokens (TYPE_4__*,int) ; 
 int /*<<< orphan*/  _cpp_push_token_context (TYPE_4__*,int /*<<< orphan*/ *,TYPE_3__ const*,int) ; 
 int /*<<< orphan*/ * collect_args (TYPE_4__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* cpp_get_token (TYPE_4__*) ; 

__attribute__((used)) static _cpp_buff *
funlike_invocation_p (cpp_reader *pfile, cpp_hashnode *node)
{
  const cpp_token *token, *padding = NULL;

  for (;;)
    {
      token = cpp_get_token (pfile);
      if (token->type != CPP_PADDING)
	break;
      if (padding == NULL
	  || (!(padding->flags & PREV_WHITE) && token->val.source == NULL))
	padding = token;
    }

  if (token->type == CPP_OPEN_PAREN)
    {
      pfile->state.parsing_args = 2;
      return collect_args (pfile, node);
    }

  /* CPP_EOF can be the end of macro arguments, or the end of the
     file.  We mustn't back up over the latter.  Ugh.  */
  if (token->type != CPP_EOF || token == &pfile->eof)
    {
      /* Back up.  We may have skipped padding, in which case backing
	 up more than one token when expanding macros is in general
	 too difficult.  We re-insert it in its own context.  */
      _cpp_backup_tokens (pfile, 1);
      if (padding)
	_cpp_push_token_context (pfile, NULL, padding, 1);
    }

  return NULL;
}