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
struct TYPE_7__ {scalar_t__ type; char* string; } ;
typedef  TYPE_1__ token_t ;
typedef  int /*<<< orphan*/  source_t ;
struct TYPE_8__ {char* string; struct TYPE_8__* next; } ;
typedef  TYPE_2__ bot_randomstring_t ;
struct TYPE_9__ {char* string; TYPE_2__* firstrandomstring; scalar_t__ numstrings; struct TYPE_9__* next; } ;
typedef  TYPE_3__ bot_randomlist_t ;
struct TYPE_10__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BOTFILESBASEFOLDER ; 
 int /*<<< orphan*/  BotLoadChatMessage (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  FreeSource (int /*<<< orphan*/ *) ; 
 scalar_t__ GetClearedHunkMemory (int) ; 
 int /*<<< orphan*/ * LoadSourceFile (char*) ; 
 int MAX_MESSAGE_SIZE ; 
 int /*<<< orphan*/  PC_CheckTokenString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PC_ExpectTokenString (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ PC_ReadToken (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  PC_SetBaseFolder (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRT_ERROR ; 
 int /*<<< orphan*/  PRT_MESSAGE ; 
 int /*<<< orphan*/  SourceError (int /*<<< orphan*/ *,char*,char*) ; 
 int Sys_MilliSeconds () ; 
 scalar_t__ TT_NAME ; 
 TYPE_4__ botimport ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,char*,int) ; 

bot_randomlist_t *BotLoadRandomStrings(char *filename)
{
	int pass, size;
	char *ptr = NULL, chatmessagestring[MAX_MESSAGE_SIZE];
	source_t *source;
	token_t token;
	bot_randomlist_t *randomlist, *lastrandom, *random;
	bot_randomstring_t *randomstring;

#ifdef DEBUG
	int starttime = Sys_MilliSeconds();
#endif //DEBUG

	size = 0;
	randomlist = NULL;
	random = NULL;
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
		randomlist = NULL; //list
		lastrandom = NULL; //last
		//
		while(PC_ReadToken(source, &token))
		{
			if (token.type != TT_NAME)
			{
				SourceError(source, "unknown random %s", token.string);
				FreeSource(source);
				return NULL;
			} //end if
			size += sizeof(bot_randomlist_t) + strlen(token.string) + 1;
			if (pass)
			{
				random = (bot_randomlist_t *) ptr;
				ptr += sizeof(bot_randomlist_t);
				random->string = ptr;
				ptr += strlen(token.string) + 1;
				strcpy(random->string, token.string);
				random->firstrandomstring = NULL;
				random->numstrings = 0;
				//
				if (lastrandom) lastrandom->next = random;
				else randomlist = random;
				lastrandom = random;
			} //end if
			if (!PC_ExpectTokenString(source, "=") ||
				!PC_ExpectTokenString(source, "{"))
			{
				FreeSource(source);
				return NULL;
			} //end if
			while(!PC_CheckTokenString(source, "}"))
			{
				if (!BotLoadChatMessage(source, chatmessagestring))
				{
					FreeSource(source);
					return NULL;
				} //end if
				size += sizeof(bot_randomstring_t) + strlen(chatmessagestring) + 1;
				if (pass)
				{
					randomstring = (bot_randomstring_t *) ptr;
					ptr += sizeof(bot_randomstring_t);
					randomstring->string = ptr;
					ptr += strlen(chatmessagestring) + 1;
					strcpy(randomstring->string, chatmessagestring);
					//
					random->numstrings++;
					randomstring->next = random->firstrandomstring;
					random->firstrandomstring = randomstring;
				} //end if
			} //end while
		} //end while
		//free the source after one pass
		FreeSource(source);
	} //end for
	botimport.Print(PRT_MESSAGE, "loaded %s\n", filename);
	//
#ifdef DEBUG
	botimport.Print(PRT_MESSAGE, "random strings %d msec\n", Sys_MilliSeconds() - starttime);
	//BotDumpRandomStringList(randomlist);
#endif //DEBUG
	//
	return randomlist;
}