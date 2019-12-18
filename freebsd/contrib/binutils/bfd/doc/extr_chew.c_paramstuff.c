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
typedef  int /*<<< orphan*/  string_type ;

/* Variables and functions */
 scalar_t__ NO_PARAMS ; 
 char at (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  catchar (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  catstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cattext (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ find (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  init_string (int /*<<< orphan*/ *) ; 
 scalar_t__ isspace (unsigned char) ; 
 int /*<<< orphan*/  overwrite_string (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pc ; 
 int /*<<< orphan*/  tos ; 

__attribute__((used)) static void
paramstuff ()
{
  unsigned int openp;
  unsigned int fname;
  unsigned int idx;
  unsigned int len;
  string_type out;
  init_string (&out);

#define NO_PARAMS 1

  /* Make sure that it's not already param'd or proto'd.  */
  if (NO_PARAMS
      || find (tos, "PARAMS") || find (tos, "PROTO") || !find (tos, "("))
    {
      catstr (&out, tos);
    }
  else
    {
      /* Find the open paren.  */
      for (openp = 0; at (tos, openp) != '(' && at (tos, openp); openp++)
	;

      fname = openp;
      /* Step back to the fname.  */
      fname--;
      while (fname && isspace ((unsigned char) at (tos, fname)))
	fname--;
      while (fname
	     && !isspace ((unsigned char) at (tos,fname))
	     && at (tos,fname) != '*')
	fname--;

      fname++;

      /* Output type, omitting trailing whitespace character(s), if
         any.  */
      for (len = fname; 0 < len; len--)
	{
	  if (!isspace ((unsigned char) at (tos, len - 1)))
	    break;
	}
      for (idx = 0; idx < len; idx++)
	catchar (&out, at (tos, idx));

      cattext (&out, "\n");	/* Insert a newline between type and fnname */

      /* Output function name, omitting trailing whitespace
         character(s), if any.  */
      for (len = openp; 0 < len; len--)
	{
	  if (!isspace ((unsigned char) at (tos, len - 1)))
	    break;
	}
      for (idx = fname; idx < len; idx++)
	catchar (&out, at (tos, idx));

      cattext (&out, " PARAMS (");

      for (idx = openp; at (tos, idx) && at (tos, idx) != ';'; idx++)
	catchar (&out, at (tos, idx));

      cattext (&out, ");\n\n");
    }
  overwrite_string (tos, &out);
  pc++;

}