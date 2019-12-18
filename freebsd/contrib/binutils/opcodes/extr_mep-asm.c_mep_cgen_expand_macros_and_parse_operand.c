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
typedef  int /*<<< orphan*/  CGEN_FIELDS ;
typedef  int /*<<< orphan*/  CGEN_CPU_DESC ;

/* Variables and functions */
 char* expand_string (char const*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* mep_cgen_parse_operand (int /*<<< orphan*/ ,int,char const**,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (char const*) ; 
 char* strstr (char const*,char*) ; 

const char *
mep_cgen_expand_macros_and_parse_operand (CGEN_CPU_DESC cd, int opindex,
					  const char ** strp_in, CGEN_FIELDS * fields)
{
  const char * errmsg = NULL;
  char *str = 0, *hold = 0;
  const char **strp = 0;

  /* Set up a new pointer to macro-expanded string.  */
  str = expand_string (*strp_in, 1);
  /* fprintf (stderr, " expanded <<%s>> to <<%s>>\n", *strp_in, str); */

  hold = str;
  strp = (const char **)(&str);

  errmsg = mep_cgen_parse_operand (cd, opindex, strp, fields);

  /* Now work out the advance.  */
  if (strlen (str) == 0)
    *strp_in += strlen (*strp_in);

  else
    {
      if (strstr (*strp_in, str))
	/* A macro-expansion was pulled off the front.  */
	*strp_in = strstr (*strp_in, str);  
      else
	/* A non-macro-expansion was pulled off the front.  */
	*strp_in += (str - hold); 
    }

  if (hold)
    free (hold);

  return errmsg;
}