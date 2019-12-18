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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int EOF ; 
 long MAX_CANON ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int getc (int /*<<< orphan*/ *) ; 
 scalar_t__ xrealloc (char*,long) ; 

__attribute__((used)) static long
TB_getline (char **lineptr, long *n, FILE *stream)
{
  char *line, *p;
  long size, copy;

  if (lineptr == NULL || n == NULL)
    {
      errno = EINVAL;
      return -1;
    }

  if (ferror (stream))
    return -1;

  /* Make sure we have a line buffer to start with.  */
  if (*lineptr == NULL || *n < 2) /* !seen and no buf yet need 2 chars.  */
    {
#ifndef MAX_CANON
#define MAX_CANON       256
#endif
      line = (char *) xrealloc (*lineptr, MAX_CANON);
      if (line == NULL)
        return -1;
      *lineptr = line;
      *n = MAX_CANON;
    }

  line = *lineptr;
  size = *n;

  copy = size;
  p = line;

  while (1)
    {
      long len;

      while (--copy > 0)
        {
          register int c = getc (stream);
          if (c == EOF)
            goto lose;
          else if ((*p++ = c) == '\n')
            goto win;
        }

      /* Need to enlarge the line buffer.  */
      len = p - line;
      size *= 2;
      line = (char *) xrealloc (line, size);
      if (line == NULL)
        goto lose;
      *lineptr = line;
      *n = size;
      p = line + len;
      copy = size - len;
    }

 lose:
  if (p == *lineptr)
    return -1;

  /* Return a partial line since we got an error in the middle.  */
 win:
#if defined(WIN32) || defined(_WIN32) || defined(__CYGWIN__) || defined(MSDOS)
  if (p - 2 >= *lineptr && p[-2] == '\r')
    p[-2] = p[-1], --p;
#endif
  *p = '\0';
  return p - *lineptr;
}