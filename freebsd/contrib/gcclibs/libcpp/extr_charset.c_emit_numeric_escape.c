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
struct _cpp_strbuf {size_t len; size_t asize; size_t* text; } ;
typedef  size_t cppchar_t ;
typedef  int /*<<< orphan*/  cpp_reader ;

/* Variables and functions */
 void* CPP_OPTION (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ OUTBUF_BLOCK_SIZE ; 
 void* XRESIZEVEC (int /*<<< orphan*/ ,size_t*,size_t) ; 
 int /*<<< orphan*/  bytes_big_endian ; 
 int /*<<< orphan*/  char_precision ; 
 int /*<<< orphan*/  uchar ; 
 int /*<<< orphan*/  wchar_precision ; 
 size_t width_to_mask (size_t) ; 

__attribute__((used)) static void
emit_numeric_escape (cpp_reader *pfile, cppchar_t n,
		     struct _cpp_strbuf *tbuf, bool wide)
{
  if (wide)
    {
      /* We have to render this into the target byte order, which may not
	 be our byte order.  */
      bool bigend = CPP_OPTION (pfile, bytes_big_endian);
      size_t width = CPP_OPTION (pfile, wchar_precision);
      size_t cwidth = CPP_OPTION (pfile, char_precision);
      size_t cmask = width_to_mask (cwidth);
      size_t nbwc = width / cwidth;
      size_t i;
      size_t off = tbuf->len;
      cppchar_t c;

      if (tbuf->len + nbwc > tbuf->asize)
	{
	  tbuf->asize += OUTBUF_BLOCK_SIZE;
	  tbuf->text = XRESIZEVEC (uchar, tbuf->text, tbuf->asize);
	}

      for (i = 0; i < nbwc; i++)
	{
	  c = n & cmask;
	  n >>= cwidth;
	  tbuf->text[off + (bigend ? nbwc - i - 1 : i)] = c;
	}
      tbuf->len += nbwc;
    }
  else
    {
      /* Note: this code does not handle the case where the target
	 and host have a different number of bits in a byte.  */
      if (tbuf->len + 1 > tbuf->asize)
	{
	  tbuf->asize += OUTBUF_BLOCK_SIZE;
	  tbuf->text = XRESIZEVEC (uchar, tbuf->text, tbuf->asize);
	}
      tbuf->text[tbuf->len++] = n;
    }
}