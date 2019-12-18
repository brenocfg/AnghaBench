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
typedef  char unichar ;
typedef  int rc_uint_type ;
typedef  char bfd_byte ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ascii_print (int /*<<< orphan*/ *,char const*,int) ; 
 int fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  indent (int /*<<< orphan*/ *,int) ; 
 scalar_t__ test_rc_datablock_text (int,char const*) ; 
 scalar_t__ test_rc_datablock_unicode (int,char const*) ; 
 int /*<<< orphan*/  unicode_print (int /*<<< orphan*/ *,char const*,int) ; 
 scalar_t__ windres_get_16 (int /*<<< orphan*/ *,char const*,int) ; 
 scalar_t__ windres_get_32 (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  wrtarget ; 

__attribute__((used)) static void
write_rc_datablock (FILE *e, rc_uint_type length, const bfd_byte *data, int has_next,
		    int hasblock, int show_comment)
{
  int plen;

  if (hasblock)
    fprintf (e, "BEGIN\n");

  if (show_comment == -1)
	  {
      if (test_rc_datablock_text(length, data))
	{
	  rc_uint_type i, c;
	  for (i = 0; i < length;)
	    {
	      indent (e, 2);
	      fprintf (e, "\"");

	      for (c = 0; i < length && c < 160 && data[i] != '\n'; c++, i++)
		;
	      if (i < length && data[i] == '\n')
		++i, ++c;
	      ascii_print (e, (const char *) &data[i - c], c);
	    fprintf (e, "\"");
	      if (i < length)
		fprintf (e, "\n");
	    }
          
	  if (i == 0)
	      {
	      indent (e, 2);
	      fprintf (e, "\"\"");
	      }
	  if (has_next)
	    fprintf (e, ",");
	  fprintf (e, "\n");
	  if (hasblock)
	    fprintf (e, "END\n");
	  return;
	  }
      if (test_rc_datablock_unicode (length, data))
	{
	  rc_uint_type i, c;
	  for (i = 0; i < length;)
	    {
	      const unichar *u;

	      u = (const unichar *) &data[i];
	      indent (e, 2);
	  fprintf (e, "L\"");
    	  
	      for (c = 0; i < length && c < 160 && u[c] != '\n'; c++, i += 2)
		;
	      if (i < length && u[c] == '\n')
		i += 2, ++c;
	      unicode_print (e, u, c);
	  fprintf (e, "\"");
	      if (i < length)
		fprintf (e, "\n");
	    }

	  if (i == 0)
	  {
	      indent (e, 2);
	      fprintf (e, "L\"\"");
	    }
	  if (has_next)
	    fprintf (e, ",");
	  fprintf (e, "\n");
	  if (hasblock)
	    fprintf (e, "END\n");
	  return;
	}

      show_comment = 0;
    }

  if (length != 0)
	      {
      rc_uint_type i, max_row;
      int first = 1;

      max_row = (show_comment ? 4 : 8);
      indent (e, 2);
      for (i = 0; i + 3 < length;)
		  {
	  rc_uint_type k;
	  rc_uint_type comment_start;
	  
	  comment_start = i;
	  
	  if (! first)
	    indent (e, 2);

	  for (k = 0; k < max_row && i + 3 < length; k++, i += 4)
		      {
	      if (k == 0)
		plen  = fprintf (e, "0x%lxL",
				 (long) windres_get_32 (&wrtarget, data + i, length - i));
			else
		plen = fprintf (e, " 0x%lxL",
				(long) windres_get_32 (&wrtarget, data + i, length - i)) - 1;
	      if (has_next || (i + 4) < length)
			  {
		  if (plen>0 && plen < 11)
		    indent (e, 11 - plen);
		  fprintf (e, ",");
			  }
		      }
	  if (show_comment)
	    {
	      fprintf (e, "\t/* ");
	      ascii_print (e, (const char *) &data[comment_start], i - comment_start);
	      fprintf (e, ".  */");
		  }
		fprintf (e, "\n");
		first = 0;
	      }

      if (i + 1 < length)
	      {
		if (! first)
	    indent (e, 2);
	  plen = fprintf (e, "0x%x",
	  		  (int) windres_get_16 (&wrtarget, data + i, length - i));
	  if (has_next || i + 2 < length)
		  {
	      if (plen > 0 && plen < 11)
		indent (e, 11 - plen);
	      fprintf (e, ",");
		      }
	  if (show_comment)
	    {
	      fprintf (e, "\t/* ");
	      ascii_print (e, (const char *) &data[i], 2);
	      fprintf (e, ".  */");
		  }
		fprintf (e, "\n");
		i += 2;
		first = 0;
	      }

      if (i < length)
	      {
		if (! first)
	    indent (e, 2);
	  fprintf (e, "\"");
	  ascii_print (e, (const char *) &data[i], 1);
	  fprintf (e, "\"");
	  if (has_next)
		  fprintf (e, ",");
		fprintf (e, "\n");
		first = 0;
	      }
    }
  if (hasblock)
    fprintf (e, "END\n");
}