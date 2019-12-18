#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  source_location ;
struct TYPE_22__ {scalar_t__ type; int /*<<< orphan*/  flags; int /*<<< orphan*/  src_loc; } ;
typedef  TYPE_2__ cpp_token ;
struct TYPE_23__ {TYPE_1__* buffer; int /*<<< orphan*/  cur_token; } ;
typedef  TYPE_3__ cpp_reader ;
struct TYPE_21__ {scalar_t__ cur; scalar_t__ rlimit; } ;

/* Variables and functions */
 scalar_t__ CLK_ASM ; 
 scalar_t__ CPP_DIV ; 
 int /*<<< orphan*/  CPP_DL_ERROR ; 
 scalar_t__ CPP_EQ ; 
 scalar_t__ CPP_OPTION (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PASTE_LEFT ; 
 int /*<<< orphan*/  _cpp_backup_tokens (TYPE_3__*,int) ; 
 int /*<<< orphan*/  _cpp_clean_line (TYPE_3__*) ; 
 TYPE_2__* _cpp_lex_direct (TYPE_3__*) ; 
 int /*<<< orphan*/  _cpp_pop_buffer (TYPE_3__*) ; 
 int /*<<< orphan*/  _cpp_temp_token (TYPE_3__*) ; 
 scalar_t__ alloca (unsigned int) ; 
 int /*<<< orphan*/  cpp_error (TYPE_3__*,int /*<<< orphan*/ ,char*,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpp_push_buffer (TYPE_3__*,unsigned char*,int,int) ; 
 unsigned char* cpp_spell_token (TYPE_3__*,TYPE_2__ const*,unsigned char*,int) ; 
 int /*<<< orphan*/  cpp_token_as_text (TYPE_3__*,TYPE_2__ const*) ; 
 int cpp_token_len (TYPE_2__ const*) ; 
 int /*<<< orphan*/  lang ; 

__attribute__((used)) static bool
paste_tokens (cpp_reader *pfile, const cpp_token **plhs, const cpp_token *rhs)
{
  unsigned char *buf, *end, *lhsend;
  cpp_token *lhs;
  unsigned int len;

  len = cpp_token_len (*plhs) + cpp_token_len (rhs) + 1;
  buf = (unsigned char *) alloca (len);
  end = lhsend = cpp_spell_token (pfile, *plhs, buf, false);

  /* Avoid comment headers, since they are still processed in stage 3.
     It is simpler to insert a space here, rather than modifying the
     lexer to ignore comments in some circumstances.  Simply returning
     false doesn't work, since we want to clear the PASTE_LEFT flag.  */
  if ((*plhs)->type == CPP_DIV && rhs->type != CPP_EQ)
    *end++ = ' ';
  end = cpp_spell_token (pfile, rhs, end, false);
  *end = '\n';

  cpp_push_buffer (pfile, buf, end - buf, /* from_stage3 */ true);
  _cpp_clean_line (pfile);

  /* Set pfile->cur_token as required by _cpp_lex_direct.  */
  pfile->cur_token = _cpp_temp_token (pfile);
  lhs = _cpp_lex_direct (pfile);
  if (pfile->buffer->cur != pfile->buffer->rlimit)
    {
      source_location saved_loc = lhs->src_loc;

      _cpp_pop_buffer (pfile);
      _cpp_backup_tokens (pfile, 1);
      *lhsend = '\0';

      /* We have to remove the PASTE_LEFT flag from the old lhs, but
	 we want to keep the new location.  */
      *lhs = **plhs;
      *plhs = lhs;
      lhs->src_loc = saved_loc;
      lhs->flags &= ~PASTE_LEFT;

      /* Mandatory error for all apart from assembler.  */
      if (CPP_OPTION (pfile, lang) != CLK_ASM)
	cpp_error (pfile, CPP_DL_ERROR,
	 "pasting \"%s\" and \"%s\" does not give a valid preprocessing token",
		   buf, cpp_token_as_text (pfile, rhs));
      return false;
    }

  *plhs = lhs;
  _cpp_pop_buffer (pfile);
  return true;
}