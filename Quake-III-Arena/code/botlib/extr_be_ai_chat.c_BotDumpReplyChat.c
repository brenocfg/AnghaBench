#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int flags; char* string; struct TYPE_8__* next; TYPE_4__* match; } ;
typedef  TYPE_2__ bot_replychatkey_t ;
struct TYPE_9__ {double priority; TYPE_5__* firstchatmessage; TYPE_2__* keys; struct TYPE_9__* next; } ;
typedef  TYPE_3__ bot_replychat_t ;
struct TYPE_10__ {scalar_t__ type; int variable; struct TYPE_10__* next; TYPE_1__* firststring; } ;
typedef  TYPE_4__ bot_matchpiece_t ;
struct TYPE_11__ {char* chatmessage; struct TYPE_11__* next; } ;
typedef  TYPE_5__ bot_chatmessage_t ;
struct TYPE_7__ {char* string; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * Log_FilePointer () ; 
 scalar_t__ MT_STRING ; 
 int RCKFL_AND ; 
 int RCKFL_GENDERFEMALE ; 
 int RCKFL_GENDERLESS ; 
 int RCKFL_GENDERMALE ; 
 int RCKFL_NAME ; 
 int RCKFL_NOT ; 
 int RCKFL_STRING ; 
 int RCKFL_VARIABLES ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

void BotDumpReplyChat(bot_replychat_t *replychat)
{
	FILE *fp;
	bot_replychat_t *rp;
	bot_replychatkey_t *key;
	bot_chatmessage_t *cm;
	bot_matchpiece_t *mp;

	fp = Log_FilePointer();
	if (!fp) return;
	fprintf(fp, "BotDumpReplyChat:\n");
	for (rp = replychat; rp; rp = rp->next)
	{
		fprintf(fp, "[");
		for (key = rp->keys; key; key = key->next)
		{
			if (key->flags & RCKFL_AND) fprintf(fp, "&");
			else if (key->flags & RCKFL_NOT) fprintf(fp, "!");
			//
			if (key->flags & RCKFL_NAME) fprintf(fp, "name");
			else if (key->flags & RCKFL_GENDERFEMALE) fprintf(fp, "female");
			else if (key->flags & RCKFL_GENDERMALE) fprintf(fp, "male");
			else if (key->flags & RCKFL_GENDERLESS) fprintf(fp, "it");
			else if (key->flags & RCKFL_VARIABLES)
			{
				fprintf(fp, "(");
				for (mp = key->match; mp; mp = mp->next)
				{
					if (mp->type == MT_STRING) fprintf(fp, "\"%s\"", mp->firststring->string);
					else fprintf(fp, "%d", mp->variable);
					if (mp->next) fprintf(fp, ", ");
				} //end for
				fprintf(fp, ")");
			} //end if
			else if (key->flags & RCKFL_STRING)
			{
				fprintf(fp, "\"%s\"", key->string);
			} //end if
			if (key->next) fprintf(fp, ", ");
			else fprintf(fp, "] = %1.0f\n", rp->priority);
		} //end for
		fprintf(fp, "{\n");
		for (cm = rp->firstchatmessage; cm; cm = cm->next)
		{
			fprintf(fp, "\t\"%s\";\n", cm->chatmessage);
		} //end for
		fprintf(fp, "}\n");
	} //end for
}