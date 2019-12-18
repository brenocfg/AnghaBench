#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bot_characteristic_t ;
struct TYPE_8__ {float skill; char* filename; TYPE_2__* c; } ;
typedef  TYPE_3__ bot_character_t ;
struct TYPE_6__ {float _float; char* string; int /*<<< orphan*/  integer; } ;
struct TYPE_7__ {scalar_t__ type; TYPE_1__ value; } ;

/* Variables and functions */
 TYPE_3__* BotCharacterFromHandle (int) ; 
 scalar_t__ CT_FLOAT ; 
 scalar_t__ CT_INTEGER ; 
 scalar_t__ CT_STRING ; 
 scalar_t__ GetClearedMemory (int) ; 
 scalar_t__ GetMemory (scalar_t__) ; 
 int MAX_CHARACTERISTICS ; 
 int MAX_CLIENTS ; 
 TYPE_3__** botcharacters ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

int BotInterpolateCharacters(int handle1, int handle2, float desiredskill)
{
	bot_character_t *ch1, *ch2, *out;
	int i, handle;
	float scale;

	ch1 = BotCharacterFromHandle(handle1);
	ch2 = BotCharacterFromHandle(handle2);
	if (!ch1 || !ch2)
		return 0;
	//find a free spot for a character
	for (handle = 1; handle <= MAX_CLIENTS; handle++)
	{
		if (!botcharacters[handle]) break;
	} //end for
	if (handle > MAX_CLIENTS) return 0;
	out = (bot_character_t *) GetClearedMemory(sizeof(bot_character_t) +
					MAX_CHARACTERISTICS * sizeof(bot_characteristic_t));
	out->skill = desiredskill;
	strcpy(out->filename, ch1->filename);
	botcharacters[handle] = out;

	scale = (float) (desiredskill - ch1->skill) / (ch2->skill - ch1->skill);
	for (i = 0; i < MAX_CHARACTERISTICS; i++)
	{
		//
		if (ch1->c[i].type == CT_FLOAT && ch2->c[i].type == CT_FLOAT)
		{
			out->c[i].type = CT_FLOAT;
			out->c[i].value._float = ch1->c[i].value._float +
								(ch2->c[i].value._float - ch1->c[i].value._float) * scale;
		} //end if
		else if (ch1->c[i].type == CT_INTEGER)
		{
			out->c[i].type = CT_INTEGER;
			out->c[i].value.integer = ch1->c[i].value.integer;
		} //end else if
		else if (ch1->c[i].type == CT_STRING)
		{
			out->c[i].type = CT_STRING;
			out->c[i].value.string = (char *) GetMemory(strlen(ch1->c[i].value.string)+1);
			strcpy(out->c[i].value.string, ch1->c[i].value.string);
		} //end else if
	} //end for
	return handle;
}