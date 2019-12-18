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
typedef  int uchar ;
struct _cpp_strbuf {int dummy; } ;
typedef  int cppchar_t ;
typedef  int /*<<< orphan*/  cpp_reader ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_DL_ERROR ; 
 int /*<<< orphan*/  CPP_DL_PEDWARN ; 
 int /*<<< orphan*/  CPP_DL_WARNING ; 
 size_t CPP_OPTION (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ CPP_WTRADITIONAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  char_precision ; 
 int /*<<< orphan*/  cpp_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  emit_numeric_escape (int /*<<< orphan*/ *,int,struct _cpp_strbuf*,int) ; 
 int /*<<< orphan*/  hex_p (int) ; 
 int hex_value (int) ; 
 int /*<<< orphan*/  wchar_precision ; 
 size_t width_to_mask (size_t) ; 

__attribute__((used)) static const uchar *
convert_hex (cpp_reader *pfile, const uchar *from, const uchar *limit,
	     struct _cpp_strbuf *tbuf, bool wide)
{
  cppchar_t c, n = 0, overflow = 0;
  int digits_found = 0;
  size_t width = (wide ? CPP_OPTION (pfile, wchar_precision)
		  : CPP_OPTION (pfile, char_precision));
  size_t mask = width_to_mask (width);

  if (CPP_WTRADITIONAL (pfile))
    cpp_error (pfile, CPP_DL_WARNING,
	       "the meaning of '\\x' is different in traditional C");

  from++;  /* Skip 'x'.  */
  while (from < limit)
    {
      c = *from;
      if (! hex_p (c))
	break;
      from++;
      overflow |= n ^ (n << 4 >> 4);
      n = (n << 4) + hex_value (c);
      digits_found = 1;
    }

  if (!digits_found)
    {
      cpp_error (pfile, CPP_DL_ERROR,
		 "\\x used with no following hex digits");
      return from;
    }

  if (overflow | (n != (n & mask)))
    {
      cpp_error (pfile, CPP_DL_PEDWARN,
		 "hex escape sequence out of range");
      n &= mask;
    }

  emit_numeric_escape (pfile, n, tbuf, wide);

  return from;
}