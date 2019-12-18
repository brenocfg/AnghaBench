#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* expanded; char const* contracted; } ;
typedef  TYPE_1__ unexpansion ;

/* Variables and functions */
 int /*<<< orphan*/  is_id_char (char const) ; 
 char* savestring (char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 void* strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char const*,size_t) ; 
 TYPE_1__* unexpansions ; 
 char* xmalloc (int) ; 
 char* xrealloc (char*,int) ; 

__attribute__((used)) static char *
unexpand_if_needed (const char *aux_info_line)
{
  static char *line_buf = 0;
  static int line_buf_size = 0;
  const unexpansion *unexp_p;
  int got_unexpanded = 0;
  const char *s;
  char *copy_p = line_buf;

  if (line_buf == 0)
    {
      line_buf_size = 1024;
      line_buf = xmalloc (line_buf_size);
    }

  copy_p = line_buf;

  /* Make a copy of the input string in line_buf, expanding as necessary.  */

  for (s = aux_info_line; *s != '\n'; )
    {
      for (unexp_p = unexpansions; unexp_p->expanded; unexp_p++)
	{
	  const char *in_p = unexp_p->expanded;
	  size_t len = strlen (in_p);

	  if (*s == *in_p && !strncmp (s, in_p, len) && !is_id_char (s[len]))
	    {
	      int size = strlen (unexp_p->contracted);
	      got_unexpanded = 1;
	      if (copy_p + size - line_buf >= line_buf_size)
		{
		  int offset = copy_p - line_buf;
		  line_buf_size *= 2;
		  line_buf_size += size;
		  line_buf = xrealloc (line_buf, line_buf_size);
		  copy_p = line_buf + offset;
		}
	      strcpy (copy_p, unexp_p->contracted);
	      copy_p += size;

	      /* Assume that there will not be another replacement required
	         within the text just replaced.  */

	      s += len;
	      goto continue_outer;
	    }
	}
      if (copy_p - line_buf == line_buf_size)
	{
	  int offset = copy_p - line_buf;
	  line_buf_size *= 2;
	  line_buf = xrealloc (line_buf, line_buf_size);
	  copy_p = line_buf + offset;
	}
      *copy_p++ = *s++;
continue_outer: ;
    }
  if (copy_p + 2 - line_buf >= line_buf_size)
    {
      int offset = copy_p - line_buf;
      line_buf_size *= 2;
      line_buf = xrealloc (line_buf, line_buf_size);
      copy_p = line_buf + offset;
    }
  *copy_p++ = '\n';
  *copy_p = '\0';

  return (got_unexpanded ? savestring (line_buf, copy_p - line_buf) : 0);
}