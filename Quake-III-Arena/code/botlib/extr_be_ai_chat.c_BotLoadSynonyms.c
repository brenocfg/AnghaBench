#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ type; unsigned long intvalue; int /*<<< orphan*/  string; scalar_t__ floatvalue; } ;
typedef  TYPE_1__ token_t ;
typedef  int /*<<< orphan*/  source_t ;
struct TYPE_9__ {unsigned long context; int /*<<< orphan*/  totalweight; TYPE_3__* firstsynonym; struct TYPE_9__* next; } ;
typedef  TYPE_2__ bot_synonymlist_t ;
struct TYPE_10__ {char* string; scalar_t__ weight; struct TYPE_10__* next; } ;
typedef  TYPE_3__ bot_synonym_t ;
struct TYPE_11__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*,char*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BOTFILESBASEFOLDER ; 
 int /*<<< orphan*/  FreeSource (int /*<<< orphan*/ *) ; 
 scalar_t__ GetClearedHunkMemory (int) ; 
 int /*<<< orphan*/ * LoadSourceFile (char*) ; 
 scalar_t__ PC_CheckTokenString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PC_ExpectTokenString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PC_ExpectTokenType (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ PC_ReadToken (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  PC_SetBaseFolder (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRT_ERROR ; 
 int /*<<< orphan*/  PRT_MESSAGE ; 
 int /*<<< orphan*/  SourceError (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  StripDoubleQuotes (int /*<<< orphan*/ ) ; 
 scalar_t__ TT_NUMBER ; 
 scalar_t__ TT_PUNCTUATION ; 
 scalar_t__ TT_STRING ; 
 TYPE_4__ botimport ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char*,char*) ; 

bot_synonymlist_t *BotLoadSynonyms(char *filename)
{
	int pass, size, contextlevel, numsynonyms;
	unsigned long int context, contextstack[32];
	char *ptr = NULL;
	source_t *source;
	token_t token;
	bot_synonymlist_t *synlist, *lastsyn, *syn;
	bot_synonym_t *synonym, *lastsynonym;

	size = 0;
	synlist = NULL; //make compiler happy
	syn = NULL; //make compiler happy
	synonym = NULL; //make compiler happy
	//the synonyms are parsed in two phases
	for (pass = 0; pass < 2; pass++)
	{
		//
		if (pass && size) ptr = (char *) GetClearedHunkMemory(size);
		//
		PC_SetBaseFolder(BOTFILESBASEFOLDER);
		source = LoadSourceFile(filename);
		if (!source)
		{
			botimport.Print(PRT_ERROR, "counldn't load %s\n", filename);
			return NULL;
		} //end if
		//
		context = 0;
		contextlevel = 0;
		synlist = NULL; //list synonyms
		lastsyn = NULL; //last synonym in the list
		//
		while(PC_ReadToken(source, &token))
		{
			if (token.type == TT_NUMBER)
			{
				context |= token.intvalue;
				contextstack[contextlevel] = token.intvalue;
				contextlevel++;
				if (contextlevel >= 32)
				{
					SourceError(source, "more than 32 context levels");
					FreeSource(source);
					return NULL;
				} //end if
				if (!PC_ExpectTokenString(source, "{"))
				{
					FreeSource(source);
					return NULL;
				} //end if
			} //end if
			else if (token.type == TT_PUNCTUATION)
			{
				if (!strcmp(token.string, "}"))
				{
					contextlevel--;
					if (contextlevel < 0)
					{
						SourceError(source, "too many }");
						FreeSource(source);
						return NULL;
					} //end if
					context &= ~contextstack[contextlevel];
				} //end if
				else if (!strcmp(token.string, "["))
				{
					size += sizeof(bot_synonymlist_t);
					if (pass)
					{
						syn = (bot_synonymlist_t *) ptr;
						ptr += sizeof(bot_synonymlist_t);
						syn->context = context;
						syn->firstsynonym = NULL;
						syn->next = NULL;
						if (lastsyn) lastsyn->next = syn;
						else synlist = syn;
						lastsyn = syn;
					} //end if
					numsynonyms = 0;
					lastsynonym = NULL;
					while(1)
					{
						if (!PC_ExpectTokenString(source, "(") ||
							!PC_ExpectTokenType(source, TT_STRING, 0, &token))
						{
							FreeSource(source);
							return NULL;
						} //end if
						StripDoubleQuotes(token.string);
						if (strlen(token.string) <= 0)
						{
							SourceError(source, "empty string", token.string);
							FreeSource(source);
							return NULL;
						} //end if
						size += sizeof(bot_synonym_t) + strlen(token.string) + 1;
						if (pass)
						{
							synonym = (bot_synonym_t *) ptr;
							ptr += sizeof(bot_synonym_t);
							synonym->string = ptr;
							ptr += strlen(token.string) + 1;
							strcpy(synonym->string, token.string);
							//
							if (lastsynonym) lastsynonym->next = synonym;
							else syn->firstsynonym = synonym;
							lastsynonym = synonym;
						} //end if
						numsynonyms++;
						if (!PC_ExpectTokenString(source, ",") ||
							!PC_ExpectTokenType(source, TT_NUMBER, 0, &token) ||
							!PC_ExpectTokenString(source, ")"))
						{
							FreeSource(source);
							return NULL;
						} //end if
						if (pass)
						{
							synonym->weight = token.floatvalue;
							syn->totalweight += synonym->weight;
						} //end if
						if (PC_CheckTokenString(source, "]")) break;
						if (!PC_ExpectTokenString(source, ","))
						{
							FreeSource(source);
							return NULL;
						} //end if
					} //end while
					if (numsynonyms < 2)
					{
						SourceError(source, "synonym must have at least two entries\n");
						FreeSource(source);
						return NULL;
					} //end if
				} //end else
				else
				{
					SourceError(source, "unexpected %s", token.string);
					FreeSource(source);
					return NULL;
				} //end if
			} //end else if
		} //end while
		//
		FreeSource(source);
		//
		if (contextlevel > 0)
		{
			SourceError(source, "missing }");
			return NULL;
		} //end if
	} //end for
	botimport.Print(PRT_MESSAGE, "loaded %s\n", filename);
	//
	//BotDumpSynonymList(synlist);
	//
	return synlist;
}