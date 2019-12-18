#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ type; double string; struct TYPE_14__* next; } ;
typedef  TYPE_1__ token_t ;
struct TYPE_15__ {int /*<<< orphan*/  defines; int /*<<< orphan*/  definehash; } ;
typedef  TYPE_2__ source_t ;
typedef  int /*<<< orphan*/  define_t ;

/* Variables and functions */
 int /*<<< orphan*/  Log_Write (char*,...) ; 
 TYPE_1__* PC_CopyToken (TYPE_1__*) ; 
 int /*<<< orphan*/  PC_EvaluateTokens (TYPE_2__*,TYPE_1__*,long*,double*,int) ; 
 int /*<<< orphan*/  PC_ExpandDefineIntoSource (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PC_FindDefine (int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/ * PC_FindHashedDefine (int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  PC_FreeToken (TYPE_1__*) ; 
 scalar_t__ PC_ReadLine (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  SourceError (TYPE_2__*,char*,...) ; 
 scalar_t__ TT_NAME ; 
 scalar_t__ TT_NUMBER ; 
 scalar_t__ TT_PUNCTUATION ; 
 int qfalse ; 
 int qtrue ; 
 int /*<<< orphan*/  strcmp (double,char*) ; 

int PC_Evaluate(source_t *source, signed long int *intvalue,
												double *floatvalue, int integer)
{
	token_t token, *firsttoken, *lasttoken;
	token_t *t, *nexttoken;
	define_t *define;
	int defined = qfalse;

	if (intvalue) *intvalue = 0;
	if (floatvalue) *floatvalue = 0;
	//
	if (!PC_ReadLine(source, &token))
	{
		SourceError(source, "no value after #if/#elif");
		return qfalse;
	} //end if
	firsttoken = NULL;
	lasttoken = NULL;
	do
	{
		//if the token is a name
		if (token.type == TT_NAME)
		{
			if (defined)
			{
				defined = qfalse;
				t = PC_CopyToken(&token);
				t->next = NULL;
				if (lasttoken) lasttoken->next = t;
				else firsttoken = t;
				lasttoken = t;
			} //end if
			else if (!strcmp(token.string, "defined"))
			{
				defined = qtrue;
				t = PC_CopyToken(&token);
				t->next = NULL;
				if (lasttoken) lasttoken->next = t;
				else firsttoken = t;
				lasttoken = t;
			} //end if
			else
			{
				//then it must be a define
#if DEFINEHASHING
				define = PC_FindHashedDefine(source->definehash, token.string);
#else
				define = PC_FindDefine(source->defines, token.string);
#endif //DEFINEHASHING
				if (!define)
				{
					SourceError(source, "can't evaluate %s, not defined", token.string);
					return qfalse;
				} //end if
				if (!PC_ExpandDefineIntoSource(source, &token, define)) return qfalse;
			} //end else
		} //end if
		//if the token is a number or a punctuation
		else if (token.type == TT_NUMBER || token.type == TT_PUNCTUATION)
		{
			t = PC_CopyToken(&token);
			t->next = NULL;
			if (lasttoken) lasttoken->next = t;
			else firsttoken = t;
			lasttoken = t;
		} //end else
		else //can't evaluate the token
		{
			SourceError(source, "can't evaluate %s", token.string);
			return qfalse;
		} //end else
	} while(PC_ReadLine(source, &token));
	//
	if (!PC_EvaluateTokens(source, firsttoken, intvalue, floatvalue, integer)) return qfalse;
	//
#ifdef DEBUG_EVAL
	Log_Write("eval:");
#endif //DEBUG_EVAL
	for (t = firsttoken; t; t = nexttoken)
	{
#ifdef DEBUG_EVAL
		Log_Write(" %s", t->string);
#endif //DEBUG_EVAL
		nexttoken = t->next;
		PC_FreeToken(t);
	} //end for
#ifdef DEBUG_EVAL
	if (integer) Log_Write("eval result: %d", *intvalue);
	else Log_Write("eval result: %f", *floatvalue);
#endif //DEBUG_EVAL
	//
	return qtrue;
}