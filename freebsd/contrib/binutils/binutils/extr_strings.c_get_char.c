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
typedef  int /*<<< orphan*/  file_off ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 long EOF ; 
 int encoding ; 
 int encoding_bytes ; 
 int getc (int /*<<< orphan*/ *) ; 
 int getc_unlocked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static long
get_char (FILE *stream, file_off *address, int *magiccount, char **magic)
{
  int c, i;
  long r = EOF;
  unsigned char buf[4];

  for (i = 0; i < encoding_bytes; i++)
    {
      if (*magiccount)
	{
	  (*magiccount)--;
	  c = *(*magic)++;
	}
      else
	{
	  if (stream == NULL)
	    return EOF;

	  /* Only use getc_unlocked if we found a declaration for it.
	     Otherwise, libc is not thread safe by default, and we
	     should not use it.  */

#if defined(HAVE_GETC_UNLOCKED) && HAVE_DECL_GETC_UNLOCKED
	  c = getc_unlocked (stream);
#else
	  c = getc (stream);
#endif
	  if (c == EOF)
	    return EOF;
	}

      (*address)++;
      buf[i] = c;
    }

  switch (encoding)
    {
    case 'S':
    case 's':
      r = buf[0];
      break;
    case 'b':
      r = (buf[0] << 8) | buf[1];
      break;
    case 'l':
      r = buf[0] | (buf[1] << 8);
      break;
    case 'B':
      r = ((long) buf[0] << 24) | ((long) buf[1] << 16) |
	((long) buf[2] << 8) | buf[3];
      break;
    case 'L':
      r = buf[0] | ((long) buf[1] << 8) | ((long) buf[2] << 16) |
	((long) buf[3] << 24);
      break;
    }

  if (r == EOF)
    return 0;

  return r;
}