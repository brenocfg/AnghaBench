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
struct exclude {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int errno ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int getc (int /*<<< orphan*/ *) ; 
 scalar_t__ is_space (char) ; 
 int /*<<< orphan*/ * stdin ; 
 void stub1 (struct exclude*,char const*,int) ; 
 char* x2realloc (char*,size_t*) ; 
 char* xrealloc (char*,size_t) ; 

int
add_exclude_file (void (*add_func) (struct exclude *, char const *, int),
		  struct exclude *ex, char const *filename, int options,
		  char line_end)
{
  bool use_stdin = filename[0] == '-' && !filename[1];
  FILE *in;
  char *buf = NULL;
  char *p;
  char const *pattern;
  char const *lim;
  size_t buf_alloc = 0;
  size_t buf_count = 0;
  int c;
  int e = 0;

  if (use_stdin)
    in = stdin;
  else if (! (in = fopen (filename, "r")))
    return -1;

  while ((c = getc (in)) != EOF)
    {
      if (buf_count == buf_alloc)
	buf = x2realloc (buf, &buf_alloc);
      buf[buf_count++] = c;
    }

  if (ferror (in))
    e = errno;

  if (!use_stdin && fclose (in) != 0)
    e = errno;

  buf = xrealloc (buf, buf_count + 1);
  buf[buf_count] = line_end;
  lim = buf + buf_count + ! (buf_count == 0 || buf[buf_count - 1] == line_end);
  pattern = buf;

  for (p = buf; p < lim; p++)
    if (*p == line_end)
      {
	char *pattern_end = p;

	if (is_space (line_end))
	  {
	    for (; ; pattern_end--)
	      if (pattern_end == pattern)
		goto next_pattern;
	      else if (! is_space (pattern_end[-1]))
		break;
	  }

	*pattern_end = '\0';
	(*add_func) (ex, pattern, options);

      next_pattern:
	pattern = p + 1;
      }

  errno = e;
  return e ? -1 : 0;
}