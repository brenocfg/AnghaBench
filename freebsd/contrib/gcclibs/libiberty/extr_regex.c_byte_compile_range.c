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
typedef  int reg_syntax_t ;
typedef  int /*<<< orphan*/  reg_errcode_t ;
typedef  int /*<<< orphan*/  RE_TRANSLATE_TYPE ;

/* Variables and functions */
 int BYTEWIDTH ; 
 int /*<<< orphan*/  LC_COLLATE ; 
 int /*<<< orphan*/  REG_ERANGE ; 
 int /*<<< orphan*/  REG_NOERROR ; 
 int RE_NO_EMPTY_RANGES ; 
 int /*<<< orphan*/  SET_LIST_BIT (unsigned int) ; 
 unsigned int TRANSLATE (char const) ; 
 int /*<<< orphan*/  _NL_COLLATE_COLLSEQMB ; 
 scalar_t__ _NL_CURRENT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static reg_errcode_t
byte_compile_range (unsigned int range_start_char, const char **p_ptr,
                    const char *pend, RE_TRANSLATE_TYPE translate,
                    reg_syntax_t syntax, unsigned char *b)
{
  unsigned this_char;
  const char *p = *p_ptr;
  reg_errcode_t ret;
# if _LIBC
  const unsigned char *collseq;
  unsigned int start_colseq;
  unsigned int end_colseq;
# else
  unsigned end_char;
# endif

  if (p == pend)
    return REG_ERANGE;

  /* Have to increment the pointer into the pattern string, so the
     caller isn't still at the ending character.  */
  (*p_ptr)++;

  /* Report an error if the range is empty and the syntax prohibits this.  */
  ret = syntax & RE_NO_EMPTY_RANGES ? REG_ERANGE : REG_NOERROR;

# if _LIBC
  collseq = (const unsigned char *) _NL_CURRENT (LC_COLLATE,
						 _NL_COLLATE_COLLSEQMB);

  start_colseq = collseq[(unsigned char) TRANSLATE (range_start_char)];
  end_colseq = collseq[(unsigned char) TRANSLATE (p[0])];
  for (this_char = 0; this_char <= (unsigned char) -1; ++this_char)
    {
      unsigned int this_colseq = collseq[(unsigned char) TRANSLATE (this_char)];

      if (start_colseq <= this_colseq && this_colseq <= end_colseq)
	{
	  SET_LIST_BIT (TRANSLATE (this_char));
	  ret = REG_NOERROR;
	}
    }
# else
  /* Here we see why `this_char' has to be larger than an `unsigned
     char' -- we would otherwise go into an infinite loop, since all
     characters <= 0xff.  */
  range_start_char = TRANSLATE (range_start_char);
  /* TRANSLATE(p[0]) is casted to char (not unsigned char) in TRANSLATE,
     and some compilers cast it to int implicitly, so following for_loop
     may fall to (almost) infinite loop.
     e.g. If translate[p[0]] = 0xff, end_char may equals to 0xffffffff.
     To avoid this, we cast p[0] to unsigned int and truncate it.  */
  end_char = ((unsigned)TRANSLATE(p[0]) & ((1 << BYTEWIDTH) - 1));

  for (this_char = range_start_char; this_char <= end_char; ++this_char)
    {
      SET_LIST_BIT (TRANSLATE (this_char));
      ret = REG_NOERROR;
    }
# endif

  return ret;
}