#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int len; char* ptr; } ;
typedef  TYPE_1__ sb ;

/* Variables and functions */
 scalar_t__ ISWHITE (char) ; 
 scalar_t__ LABELS_WITHOUT_COLONS ; 
 scalar_t__ NO_PSEUDO_DOT ; 
 int /*<<< orphan*/  flag_m68k_mri ; 
 int /*<<< orphan*/  is_name_beginner (char) ; 
 scalar_t__ is_name_ender (char) ; 
 scalar_t__ is_part_of_name (char) ; 
 scalar_t__ macro_mri ; 
 int /*<<< orphan*/  sb_add_char (TYPE_1__*,int) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 
 int strlen (char const*) ; 
 scalar_t__ strncasecmp (char*,char const*,int) ; 

int
buffer_and_nest (const char *from, const char *to, sb *ptr,
		 int (*get_line) (sb *))
{
  int from_len;
  int to_len = strlen (to);
  int depth = 1;
  int line_start = ptr->len;

  int more = get_line (ptr);

  if (to_len == 4 && strcasecmp(to, "ENDR") == 0)
    {
      from = NULL;
      from_len = 0;
    }
  else
    from_len = strlen (from);

  while (more)
    {
      /* Try to find the first pseudo op on the line.  */
      int i = line_start;

      /* With normal syntax we can suck what we want till we get
	 to the dot.  With the alternate, labels have to start in
	 the first column, since we can't tell what's a label and
	 what's a pseudoop.  */

      if (! LABELS_WITHOUT_COLONS)
	{
	  /* Skip leading whitespace.  */
	  while (i < ptr->len && ISWHITE (ptr->ptr[i]))
	    i++;
	}

      for (;;)
	{
	  /* Skip over a label, if any.  */
	  if (i >= ptr->len || ! is_name_beginner (ptr->ptr[i]))
	    break;
	  i++;
	  while (i < ptr->len && is_part_of_name (ptr->ptr[i]))
	    i++;
	  if (i < ptr->len && is_name_ender (ptr->ptr[i]))
	    i++;
	  if (LABELS_WITHOUT_COLONS)
	    break;
	  /* Skip whitespace.  */
	  while (i < ptr->len && ISWHITE (ptr->ptr[i]))
	    i++;
	  /* Check for the colon.  */
	  if (i >= ptr->len || ptr->ptr[i] != ':')
	    {
	      i = line_start;
	      break;
	    }
	  i++;
	  line_start = i;
	}

      /* Skip trailing whitespace.  */
      while (i < ptr->len && ISWHITE (ptr->ptr[i]))
	i++;

      if (i < ptr->len && (ptr->ptr[i] == '.'
			   || NO_PSEUDO_DOT
			   || macro_mri))
	{
	  if (! flag_m68k_mri && ptr->ptr[i] == '.')
	    i++;
	  if (from == NULL
	     && strncasecmp (ptr->ptr + i, "IRPC", from_len = 4) != 0
	     && strncasecmp (ptr->ptr + i, "IRP", from_len = 3) != 0
	     && strncasecmp (ptr->ptr + i, "IREPC", from_len = 5) != 0
	     && strncasecmp (ptr->ptr + i, "IREP", from_len = 4) != 0
	     && strncasecmp (ptr->ptr + i, "REPT", from_len = 4) != 0
	     && strncasecmp (ptr->ptr + i, "REP", from_len = 3) != 0)
	    from_len = 0;
	  if ((from != NULL
	       ? strncasecmp (ptr->ptr + i, from, from_len) == 0
	       : from_len > 0)
	      && (ptr->len == (i + from_len)
		  || ! (is_part_of_name (ptr->ptr[i + from_len])
			|| is_name_ender (ptr->ptr[i + from_len]))))
	    depth++;
	  if (strncasecmp (ptr->ptr + i, to, to_len) == 0
	      && (ptr->len == (i + to_len)
		  || ! (is_part_of_name (ptr->ptr[i + to_len])
			|| is_name_ender (ptr->ptr[i + to_len]))))
	    {
	      depth--;
	      if (depth == 0)
		{
		  /* Reset the string to not include the ending rune.  */
		  ptr->len = line_start;
		  break;
		}
	    }
	}

      /* Add the original end-of-line char to the end and keep running.  */
      sb_add_char (ptr, more);
      line_start = ptr->len;
      more = get_line (ptr);
    }

  /* Return 1 on success, 0 on unexpected EOF.  */
  return depth == 0;
}