#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  char uchar ;
typedef  enum cpp_ttype { ____Placeholder_cpp_ttype } cpp_ttype ;
typedef  char cppchar_t ;
typedef  int /*<<< orphan*/  cpp_token ;
struct TYPE_8__ {int /*<<< orphan*/  skipping; int /*<<< orphan*/  in_diagnostic; int /*<<< orphan*/  angled_headers; } ;
struct TYPE_10__ {TYPE_2__* buffer; TYPE_1__ state; } ;
typedef  TYPE_3__ cpp_reader ;
struct TYPE_9__ {char const* cur; } ;

/* Variables and functions */
 scalar_t__ CLK_ASM ; 
 int CPP_CHAR ; 
 int /*<<< orphan*/  CPP_DL_PEDWARN ; 
 int /*<<< orphan*/  CPP_DL_WARNING ; 
 int CPP_HEADER_NAME ; 
 scalar_t__ CPP_OPTION (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int CPP_OTHER ; 
 int CPP_STRING ; 
 int CPP_WCHAR ; 
 int CPP_WSTRING ; 
 int /*<<< orphan*/  cpp_error (TYPE_3__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  create_literal (TYPE_3__*,int /*<<< orphan*/ *,char const*,int,int) ; 
 int /*<<< orphan*/  lang ; 

__attribute__((used)) static void
lex_string (cpp_reader *pfile, cpp_token *token, const uchar *base)
{
  bool saw_NUL = false;
  const uchar *cur;
  cppchar_t terminator;
  enum cpp_ttype type;

  cur = base;
  terminator = *cur++;
  if (terminator == 'L')
    terminator = *cur++;
  if (terminator == '\"')
    type = *base == 'L' ? CPP_WSTRING: CPP_STRING;
  else if (terminator == '\'')
    type = *base == 'L' ? CPP_WCHAR: CPP_CHAR;
  else
    terminator = '>', type = CPP_HEADER_NAME;

  for (;;)
    {
      cppchar_t c = *cur++;

      /* In #include-style directives, terminators are not escapable.  */
      if (c == '\\' && !pfile->state.angled_headers && *cur != '\n')
	cur++;
      else if (c == terminator)
	break;
      else if (c == '\n')
	{
	  cur--;
	  type = CPP_OTHER;
	  break;
	}
      else if (c == '\0')
	saw_NUL = true;
    }

  if (saw_NUL && !pfile->state.skipping)
    cpp_error (pfile, CPP_DL_WARNING,
	       "null character(s) preserved in literal");

  /* APPLE LOCAL begin #error with unmatched quotes 5607574 */
  if (type == CPP_OTHER
      && CPP_OPTION (pfile, lang) != CLK_ASM
      && !pfile->state.in_diagnostic
      && !pfile->state.skipping)
  /* APPLE LOCAL end #error with unmatched quotes 5607574 */
    cpp_error (pfile, CPP_DL_PEDWARN, "missing terminating %c character",
	       (int) terminator);

  pfile->buffer->cur = cur;
  create_literal (pfile, token, base, cur - base, type);
}