#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ type; int subtype; unsigned long intvalue; int /*<<< orphan*/  string; } ;
typedef  TYPE_1__ token_t ;
typedef  int /*<<< orphan*/  source_t ;
struct TYPE_9__ {unsigned long context; unsigned long type; unsigned long subtype; int /*<<< orphan*/  first; struct TYPE_9__* next; } ;
typedef  TYPE_2__ bot_matchtemplate_t ;
struct TYPE_10__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*,char*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BOTFILESBASEFOLDER ; 
 int /*<<< orphan*/  BotFreeMatchTemplates (TYPE_2__*) ; 
 int /*<<< orphan*/  BotLoadMatchPieces (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  FreeSource (int /*<<< orphan*/ *) ; 
 scalar_t__ GetClearedHunkMemory (int) ; 
 int /*<<< orphan*/ * LoadSourceFile (char*) ; 
 int /*<<< orphan*/  PC_ExpectTokenString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PC_ExpectTokenType (int /*<<< orphan*/ *,scalar_t__,int,TYPE_1__*) ; 
 scalar_t__ PC_ReadToken (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  PC_SetBaseFolder (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PC_UnreadLastToken (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PRT_ERROR ; 
 int /*<<< orphan*/  PRT_MESSAGE ; 
 int /*<<< orphan*/  SourceError (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int TT_INTEGER ; 
 scalar_t__ TT_NUMBER ; 
 TYPE_3__ botimport ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char*,char*) ; 

bot_matchtemplate_t *BotLoadMatchTemplates(char *matchfile)
{
	source_t *source;
	token_t token;
	bot_matchtemplate_t *matchtemplate, *matches, *lastmatch;
	unsigned long int context;

	PC_SetBaseFolder(BOTFILESBASEFOLDER);
	source = LoadSourceFile(matchfile);
	if (!source)
	{
		botimport.Print(PRT_ERROR, "counldn't load %s\n", matchfile);
		return NULL;
	} //end if
	//
	matches = NULL; //list with matches
	lastmatch = NULL; //last match in the list

	while(PC_ReadToken(source, &token))
	{
		if (token.type != TT_NUMBER || !(token.subtype & TT_INTEGER))
		{
			SourceError(source, "expected integer, found %s\n", token.string);
			BotFreeMatchTemplates(matches);
			FreeSource(source);
			return NULL;
		} //end if
		//the context
		context = token.intvalue;
		//
		if (!PC_ExpectTokenString(source, "{"))
		{
			BotFreeMatchTemplates(matches);
			FreeSource(source);
			return NULL;
		} //end if
		//
		while(PC_ReadToken(source, &token))
		{
			if (!strcmp(token.string, "}")) break;
			//
			PC_UnreadLastToken(source);
			//
			matchtemplate = (bot_matchtemplate_t *) GetClearedHunkMemory(sizeof(bot_matchtemplate_t));
			matchtemplate->context = context;
			matchtemplate->next = NULL;
			//add the match template to the list
			if (lastmatch) lastmatch->next = matchtemplate;
			else matches = matchtemplate;
			lastmatch = matchtemplate;
			//load the match template
			matchtemplate->first = BotLoadMatchPieces(source, "=");
			if (!matchtemplate->first)
			{
				BotFreeMatchTemplates(matches);
				return NULL;
			} //end if
			//read the match type
			if (!PC_ExpectTokenString(source, "(") ||
				!PC_ExpectTokenType(source, TT_NUMBER, TT_INTEGER, &token))
			{
				BotFreeMatchTemplates(matches);
				FreeSource(source);
				return NULL;
			} //end if
			matchtemplate->type = token.intvalue;
			//read the match subtype
			if (!PC_ExpectTokenString(source, ",") ||
				!PC_ExpectTokenType(source, TT_NUMBER, TT_INTEGER, &token))
			{
				BotFreeMatchTemplates(matches);
				FreeSource(source);
				return NULL;
			} //end if
			matchtemplate->subtype = token.intvalue;
			//read trailing punctuations
			if (!PC_ExpectTokenString(source, ")") ||
				!PC_ExpectTokenString(source, ";"))
			{
				BotFreeMatchTemplates(matches);
				FreeSource(source);
				return NULL;
			} //end if
		} //end while
	} //end while
	//free the source
	FreeSource(source);
	botimport.Print(PRT_MESSAGE, "loaded %s\n", matchfile);
	//
	//BotDumpMatchTemplates(matches);
	//
	return matches;
}