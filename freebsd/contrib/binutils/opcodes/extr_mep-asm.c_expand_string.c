#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* name; } ;
typedef  TYPE_1__ macro ;
struct TYPE_7__ {char const* start; int /*<<< orphan*/  len; } ;
typedef  TYPE_2__ arg ;

/* Variables and functions */
#define  IN_ARGS 129 
#define  IN_TEXT 128 
 int MAXARGS ; 
 char* expand_macro (TYPE_2__*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_1__* lookup_macro (char const*) ; 
 char* str_append (char*,char const*,int) ; 
 int strlen (char*) ; 

__attribute__((used)) static char *
expand_string (const char *in, int first_only)
{
  int num_expansions = 0;
  int depth = 0;
  int narg = -1;
  arg args[MAXARGS];
  int state = IN_TEXT;
  const char *mark = in;
  macro *macro = 0;

  char *expansion = 0;
  char *result = 0;

  while (*in)
    {
      switch (state)
	{
	case IN_TEXT:
	  if (*in == '%' && *(in + 1) && (!first_only || num_expansions == 0)) 
	    {	      
	      macro = lookup_macro (in + 1);
	      if (macro)
		{
		  /* printf("entering state %d at '%s'...\n", state, in); */
		  result = str_append (result, mark, in - mark);
		  mark = in;
		  in += 1 + strlen (macro->name);
		  while (*in == ' ') ++in;
		  if (*in != '(')
		    {
		      state = IN_TEXT;		      
		      macro = 0;
		    }
		  else
		    {
		      state = IN_ARGS;
		      narg = 0;
		      args[narg].start = in + 1;
		      args[narg].len = 0;
		      mark = in + 1;	      		      
		    }
		}
	    }
	  break;
	case IN_ARGS:
	  if (depth == 0)
	    {
	      switch (*in)
		{
		case ',':
		  narg++;
		  args[narg].start = (in + 1);
		  args[narg].len = 0;
		  break;
		case ')':
		  state = IN_TEXT;
		  /* printf("entering state %d at '%s'...\n", state, in); */
		  if (macro)
		    {
		      expansion = 0;
		      expansion = expand_macro (args, narg, macro);
		      num_expansions++;
		      if (expansion)
			{
			  result = str_append (result, expansion, strlen (expansion));
			  free (expansion);
			}
		    }
		  else
		    {
		      result = str_append (result, mark, in - mark);
		    }
		  macro = 0;
		  mark = in + 1;
		  break;
		case '(':
		  depth++;
		default:
		  args[narg].len++;
		  break;		  
		}
	    } 
	  else
	    {
	      if (*in == ')')
		depth--;
	      if (narg > -1)
		args[narg].len++;
	    }
	  
	}
      ++in;
    }
  
  if (mark != in)
    result = str_append (result, mark, in - mark);
  
  return result;
}