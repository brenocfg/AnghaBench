#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  char cppchar_t ;
struct TYPE_11__ {unsigned int len; unsigned char* text; } ;
struct TYPE_12__ {TYPE_2__ str; } ;
struct TYPE_14__ {TYPE_3__ val; int /*<<< orphan*/  type; } ;
typedef  TYPE_5__ cpp_token ;
struct TYPE_13__ {scalar_t__ in_directive; } ;
struct TYPE_15__ {TYPE_4__ state; TYPE_1__* buffer; } ;
typedef  TYPE_6__ cpp_reader ;
struct TYPE_10__ {unsigned char const* cur; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_COMMENT ; 
 unsigned char* _cpp_unaligned_alloc (TYPE_6__*,unsigned int) ; 
 scalar_t__ is_vspace (unsigned char const) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,unsigned int) ; 

__attribute__((used)) static void
save_comment (cpp_reader *pfile, cpp_token *token, const unsigned char *from,
	      cppchar_t type)
{
  unsigned char *buffer;
  unsigned int len, clen;

  len = pfile->buffer->cur - from + 1; /* + 1 for the initial '/'.  */

  /* C++ comments probably (not definitely) have moved past a new
     line, which we don't want to save in the comment.  */
  if (is_vspace (pfile->buffer->cur[-1]))
    len--;

  /* If we are currently in a directive, then we need to store all
     C++ comments as C comments internally, and so we need to
     allocate a little extra space in that case.

     Note that the only time we encounter a directive here is
     when we are saving comments in a "#define".  */
  clen = (pfile->state.in_directive && type == '/') ? len + 2 : len;

  buffer = _cpp_unaligned_alloc (pfile, clen);

  token->type = CPP_COMMENT;
  token->val.str.len = clen;
  token->val.str.text = buffer;

  buffer[0] = '/';
  memcpy (buffer + 1, from, len - 1);

  /* Finish conversion to a C comment, if necessary.  */
  if (pfile->state.in_directive && type == '/')
    {
      buffer[1] = '*';
      buffer[clen - 2] = '*';
      buffer[clen - 1] = '/';
    }
}