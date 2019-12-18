#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* string; struct TYPE_8__* next; } ;
typedef  TYPE_2__ bot_matchstring_t ;
struct TYPE_9__ {scalar_t__ type; size_t variable; TYPE_2__* firststring; struct TYPE_9__* next; } ;
typedef  TYPE_3__ bot_matchpiece_t ;
struct TYPE_10__ {char* string; TYPE_1__* variables; } ;
typedef  TYPE_4__ bot_match_t ;
struct TYPE_7__ {int length; int offset; } ;

/* Variables and functions */
 scalar_t__ MT_STRING ; 
 scalar_t__ MT_VARIABLE ; 
 int StringContains (char*,char*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int qfalse ; 
 int qtrue ; 
 int strlen (char*) ; 

int StringsMatch(bot_matchpiece_t *pieces, bot_match_t *match)
{
	int lastvariable, index;
	char *strptr, *newstrptr;
	bot_matchpiece_t *mp;
	bot_matchstring_t *ms;

	//no last variable
	lastvariable = -1;
	//pointer to the string to compare the match string with
	strptr = match->string;
	//Log_Write("match: %s", strptr);
	//compare the string with the current match string
	for (mp = pieces; mp; mp = mp->next)
	{
		//if it is a piece of string
		if (mp->type == MT_STRING)
		{
			newstrptr = NULL;
			for (ms = mp->firststring; ms; ms = ms->next)
			{
				if (!strlen(ms->string))
				{
					newstrptr = strptr;
					break;
				} //end if
				//Log_Write("MT_STRING: %s", mp->string);
				index = StringContains(strptr, ms->string, qfalse);
				if (index >= 0)
				{
					newstrptr = strptr + index;
					if (lastvariable >= 0)
					{
						match->variables[lastvariable].length =
								(newstrptr - match->string) - match->variables[lastvariable].offset;
								//newstrptr - match->variables[lastvariable].ptr;
						lastvariable = -1;
						break;
					} //end if
					else if (index == 0)
					{
						break;
					} //end else
					newstrptr = NULL;
				} //end if
			} //end for
			if (!newstrptr) return qfalse;
			strptr = newstrptr + strlen(ms->string);
		} //end if
		//if it is a variable piece of string
		else if (mp->type == MT_VARIABLE)
		{
			//Log_Write("MT_VARIABLE");
			match->variables[mp->variable].offset = strptr - match->string;
			lastvariable = mp->variable;
		} //end else if
	} //end for
	//if a match was found
	if (!mp && (lastvariable >= 0 || !strlen(strptr)))
	{
		//if the last piece was a variable string
		if (lastvariable >= 0)
		{
        		assert( match->variables[lastvariable].offset >= 0 ); // bk001204
			match->variables[lastvariable].length =
				strlen(&match->string[ (int) match->variables[lastvariable].offset]);
		} //end if
		return qtrue;
	} //end if
	return qfalse;
}