#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ type; int flags; } ;
typedef  TYPE_2__ cpp_token ;
struct TYPE_10__ {int in_directive; } ;
struct TYPE_12__ {TYPE_1__ state; } ;
typedef  TYPE_3__ cpp_reader ;

/* Variables and functions */
 scalar_t__ CPP_HASH ; 
 scalar_t__ CPP_NUMBER ; 
 int PREV_WHITE ; 
 int /*<<< orphan*/  _cpp_backup_tokens (TYPE_3__*,int) ; 
 int /*<<< orphan*/  _cpp_handle_directive (TYPE_3__*,int) ; 
 TYPE_2__* _cpp_lex_direct (TYPE_3__*) ; 
 int /*<<< orphan*/  read_original_directory (TYPE_3__*) ; 

__attribute__((used)) static void
read_original_filename (cpp_reader *pfile)
{
  const cpp_token *token, *token1;

  /* Lex ahead; if the first tokens are of the form # NUM, then
     process the directive, otherwise back up.  */
  token = _cpp_lex_direct (pfile);
  if (token->type == CPP_HASH)
    {
      pfile->state.in_directive = 1;
      token1 = _cpp_lex_direct (pfile);
      _cpp_backup_tokens (pfile, 1);
      pfile->state.in_directive = 0;

      /* If it's a #line directive, handle it.  */
      if (token1->type == CPP_NUMBER)
	{
	  _cpp_handle_directive (pfile, token->flags & PREV_WHITE);
	  read_original_directory (pfile);
	  return;
	}
    }

  /* Backup as if nothing happened.  */
  _cpp_backup_tokens (pfile, 1);
}