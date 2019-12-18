#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uchar ;
struct TYPE_20__ {scalar_t__ in_directive; } ;
struct TYPE_22__ {TYPE_3__* buffer; int /*<<< orphan*/  cur_token; TYPE_2__ state; } ;
typedef  TYPE_4__ cpp_reader ;
struct TYPE_19__ {scalar_t__ builtin; } ;
struct TYPE_23__ {TYPE_1__ value; } ;
typedef  TYPE_5__ cpp_hashnode ;
struct TYPE_21__ {scalar_t__ cur; scalar_t__ rlimit; } ;

/* Variables and functions */
 scalar_t__ BT_PRAGMA ; 
 int /*<<< orphan*/  CPP_DL_ICE ; 
 int /*<<< orphan*/  NODE_NAME (TYPE_5__*) ; 
 int /*<<< orphan*/ * _cpp_builtin_macro_text (TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  _cpp_clean_line (TYPE_4__*) ; 
 int /*<<< orphan*/  _cpp_do__Pragma (TYPE_4__*) ; 
 int /*<<< orphan*/  _cpp_lex_direct (TYPE_4__*) ; 
 int /*<<< orphan*/  _cpp_pop_buffer (TYPE_4__*) ; 
 int /*<<< orphan*/  _cpp_push_token_context (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _cpp_temp_token (TYPE_4__*) ; 
 scalar_t__ alloca (size_t) ; 
 int /*<<< orphan*/  cpp_error (TYPE_4__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpp_push_buffer (TYPE_4__*,int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/  const*,size_t) ; 
 size_t ustrlen (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int
builtin_macro (cpp_reader *pfile, cpp_hashnode *node)
{
  const uchar *buf;
  size_t len;
  char *nbuf;

  if (node->value.builtin == BT_PRAGMA)
    {
      /* Don't interpret _Pragma within directives.  The standard is
         not clear on this, but to me this makes most sense.  */
      if (pfile->state.in_directive)
	return 0;

      _cpp_do__Pragma (pfile);
      return 1;
    }

  buf = _cpp_builtin_macro_text (pfile, node);
  len = ustrlen (buf);
  nbuf = (char *) alloca (len + 1);
  memcpy (nbuf, buf, len);
  nbuf[len]='\n';

  cpp_push_buffer (pfile, (uchar *) nbuf, len, /* from_stage3 */ true);
  _cpp_clean_line (pfile);

  /* Set pfile->cur_token as required by _cpp_lex_direct.  */
  pfile->cur_token = _cpp_temp_token (pfile);
  _cpp_push_token_context (pfile, NULL, _cpp_lex_direct (pfile), 1);
  if (pfile->buffer->cur != pfile->buffer->rlimit)
    cpp_error (pfile, CPP_DL_ICE, "invalid built-in macro \"%s\"",
	       NODE_NAME (node));
  _cpp_pop_buffer (pfile);

  return 1;
}